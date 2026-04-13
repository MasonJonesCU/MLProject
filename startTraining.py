from aiTrainer import train

path = "easy0op" #the directory from root that has the csv you want to train off of and where the model will be saved to
numEpochs = 250
batchSize = 32
learningRate = 0.0005
train(path, numEpochs, batchSize, learningRate)