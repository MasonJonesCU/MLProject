import torch
from mathModel import MathModel
import csv
import numpy as np
import math
from util import predict

def vaildate(path):
    equations = []
    answers = []

    with open(path + "\\validation.csv", mode = 'r', newline = '') as file: #loads the validation.csv
        validationSet = csv.DictReader(file)
        for row in validationSet:
            equations.append(row['Equation'])
            answers.append(row['Answer'])

    checkpoint = torch.load(path + "\\model_full.pth", weights_only = False) #loads the model
    tokenToIndex = checkpoint["token_to_index"]
    mean = checkpoint["mean"]
    std = checkpoint["std"]
    maxLen = checkpoint["max_len"]

    vocabSize = len(tokenToIndex) #remakes the parts of the model needed
    model = MathModel(vocabSize)
    model.load_state_dict(checkpoint["model_state"])
    model.eval()

    overallAccuracy = []

    for i in range(len(equations)):
        predictedAnswer = predict(equations[i], model, std, mean, maxLen, tokenToIndex)
        if(predictedAnswer == 0 and float(answers[i]) == 0): #manually check 0 to avoid divide by zero
            accuracy = 100.0
        elif(float(answers[i]) == 0):
            accuracy = max(0, (1 - np.abs(predictedAnswer)) * 100) #tolerence of 1 when true answer is zero
        else:
            accuracy = (1 - np.abs(predictedAnswer - float(answers[i])) / (np.abs(float(answers[i])) + np.abs(predictedAnswer))) * 100 #accuracy based on difference of magnitude between asnwers
        if(not math.isnan(accuracy) and not math.isinf(accuracy)): #only use non inf/nan numbers to calcuate overall accuracy
            overallAccuracy.append(accuracy)
        print(f"Predicted answer for {equations[i]}: {predictedAnswer}. Actual: {answers[i]}. Accuracy: {accuracy}%\n")

    print(f"Overall accuracy: {np.mean(overallAccuracy)}%\n")