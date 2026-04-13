import torch.nn as nn
import torch
from torch.utils.data import Dataset
import numpy as np
from util import tokenize_equation, encode_equation

class MathModel(nn.Module):
    def __init__(self, vocabSize, embedSize=128, hiddenSize=512):
        super().__init__()
        self.embedding = nn.Embedding(vocabSize, embedSize, padding_idx=0)
        self.lstm = nn.LSTM(embedSize, hiddenSize, batch_first=True) #using lstm
        self.fc = nn.Linear(hiddenSize, 1)

    def forward(self, x):
        x = self.embedding(x)
        _, (h, _) = self.lstm(x)
        x = h.squeeze(0)
        x = self.fc(x)
        return x

class MathDataset(Dataset):
    def __init__(self, dataframe, maxLen=20):
        self.data = dataframe
        self.maxLen = maxLen

        self.tokens = self.build_token_set() #build tokens
        self.tokenToIndex = {tok: idx+1 for idx, tok in enumerate(sorted(self.tokens))}
        self.tokenToIndex["<PAD>"] = 0  #padding token
        self.indexToToken = {idx: tok for tok, idx in self.tokenToIndex.items()}

        self.mean = self.data['Answer'].mean() #overall mean used in normalization
        self.std = self.data['Answer'].std() #overall std used in normalization
        if self.std == 0 or np.isnan(self.std): #make std 1 if nan or 0
            self.std = 1.0

    def build_token_set(self): #creates the set of tokens for given equation
        tokenSet = set()
        for eq in self.data['Equation']:
            tokenSet.update(tokenize_equation(eq))
        return tokenSet

    def __len__(self):
        return len(self.data)

    def __getitem__(self, idx):
        equation = self.data.iloc[idx]['Equation']
        answer = self.data.iloc[idx]['Answer']

        answer = (answer - self.mean) / self.std

        equationTensor = encode_equation(equation, self.maxLen, self.tokenToIndex)
        return equationTensor, torch.tensor(answer, dtype=torch.float)