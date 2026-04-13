import torch
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
import pandas as pd
import numpy as np
from mathModel import MathModel, MathDataset

def train(path, noEpochs, batchSize, learningRate):
    df = pd.read_csv(path + '/dataset.csv')
    df = df.replace([np.inf, -np.inf], np.nan)
    df = df.dropna(subset=['Answer'])

    dataset = MathDataset(df) #load the dataset and loader
    dataloader = DataLoader(dataset, batch_size=batchSize, shuffle=True)

    vocabSize = len(dataset.tokenToIndex)
    model = MathModel(vocabSize)

    criterion = nn.MSELoss() #using minimum square error
    optimizer = optim.Adam(model.parameters(), lr=learningRate)

    for epoch in range(noEpochs): #training loop
        model.train()
        runningLoss = 0.0
        for inputs, targets in dataloader:
            optimizer.zero_grad()
            outputs = model(inputs)  #forward pass
            loss = criterion(outputs.view(-1), targets.view(-1))  #calculate loss
            loss.backward()  #backpropagation
            torch.nn.utils.clip_grad_norm_(model.parameters(), 1.0)
            optimizer.step()  #update the model
            runningLoss += loss.item()

        print(f"Epoch {epoch+1}/{noEpochs}, Loss: {runningLoss / len(dataloader)}")

    torch.save({ #save everything for future inqury
        "model_state": model.state_dict(),
        "token_to_index": dataset.tokenToIndex,
        "mean": dataset.mean,
        "std": dataset.std,
        "max_len": dataset.maxLen
    }, path + "/model_full.pth")