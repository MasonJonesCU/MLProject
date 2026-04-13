## Personal Project

## Mason Jones

# How to Use:

There are two python files related to running the neural network, "startTraining.py" and "startTesting.py". One trains, the other tests. Both of these files have a path variable that needs to be set to the directory containing "dataset.csv" for startTraining.py, or "model_full.pth" and "validation.csv" for startTesting.py. startTraining.py will output "model_full.pth" in the same directory as the "dataset.csv" it is trained off of.


A Full Example Runthrough:


    I create a dataset.csv with datamaker, and I put it in a folder named "example" at the root of this directory. I will then go into "startTraining.py" and change the "path" variable on line 3 to equal "example" and then run startTraining.py. After its done, "model_full.pth" will appear in the "example" folder. I will create another dataset called validation.csv with datamaker again, then move that file to the "example" folder. I then go into the "startTesting.py" file and change the "path" variable on line 3 to equal "example" and then run it. It will then tell me the accuracy of the model.


# Datamaker:

The datamaker folder includes the tool used to create the dataset and validation csvs. Instructions for how to use that tool will be in /datamaker/README.md.

# Report

A report explaining what and why as well as the results of this assignment are in "Report.pdf".

# Other folders:

There are a slew of other folders named easy/medium/hard + 0/1/2/3/4 + op. These folders contain a model trained on off the dataset that is also in the folder and tested with the validation.csv with them. These are the ones I used to construct my report. The naming scheme tells what the dataset is like, its difficulty being easy, medium, or hard, with 0-4 new operators used. What the operators are and what the difficulty means are defined within the datamaker folder. The ...Expanded folders are the same model as their non-expanded counterparts, but with test sets that exceed the range they were trained off of to simulate equations the model has never seen.

# Other files:

The remaining files are used in "startTraining.py" and "startTesting.py". "mathModel.py" contains the MathModel and MathDataset classes Pytorch uses. "aiTrainer.py" contains the train() function used to facilitate the training loop. "aiTester.py" contains the validate() function which uses the "model_full.pth" to restore the model and ask it questions and return how accurate the answers are. "util.py" contains utility function that are used in other fils.

# Dependencies:

Pytorch

Numpy

Pandas

Python 3.12 (other versions could be supported, this is the one I used)

C++ standard library and compiler if you intend to use datamaker

# Languages:

Python used for training and testing the neural network.
C++ used for the datamaker tool.