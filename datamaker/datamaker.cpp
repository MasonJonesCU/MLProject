#include <iostream>
#include <fstream>
#include <time.h>
#include "complexityDriver.h"
#include "easy.h"
#include "medium.h"
#include "hard.h"

int main(){
    srand(time(NULL));
    int noOfEquations = 100000; //set this to the total number of equations you want to generate
    Difficulty* difficulty = new Easy(); //set this to either Easy(), Medium(), or Hard()
    int noOfOperators = 0; //set this to the amount of new operators you want (0 - 4)
    Complexity equationMaker = Complexity(difficulty, noOfOperators);
    std::ofstream file("dataset.csv"); //open file

    if(!file.is_open()){ //check for problems, exit if file can't be opened
        std::cout << "Failed to open file\n";
        return 1;
    }
    std::string equation;
    std::string solution;
    file << "Equation,Answer\n"; //create the csv column names
    for(int i = 0; i < noOfEquations; i++){
        equation = equationMaker.getEquation(); //get a random equation
        solution = equationMaker.solve(equation); //get a solution to said equation
        if(i != noOfEquations - 1){ //this is to make sure the last equation doesn't have a newline
           file << equation << "," << solution << "\n"; //add newline if not the last equation
        } else {
            file << equation << "," << solution; //do not add newline if last equation
        }
        
    }
    file.close(); //close the file

    return 0;
}