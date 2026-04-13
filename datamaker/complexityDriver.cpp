#include "complexityDriver.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cctype>
#include <cmath>

Complexity::Complexity(Difficulty* difficulty, int newOperators){ //sets up the varibles used in creating equations based on the parameters set
    this -> difficulty = difficulty;
    if(newOperators > 4){ //make sure the amount of new operators is in range
        this -> newOperators = 4;
        std::cout << this -> newOperators;
    } else if(newOperators <= -1){
       this -> newOperators = 0; 
    } else {
        this -> newOperators = newOperators;
    }
    validOperators[0] = '+'; //allow the four basic operators to be used
    validOperators[1] = '-';
    validOperators[2] = '*';
    validOperators[3] = '/';
    switch(this -> difficulty -> getDifficulty()){
    case Difficulty::stype::E: //add no new established operators if easy
        break;
    case Difficulty::stype::M: //add modulo to be used if medium or higher
        validOperators[4] = '%';
        break;
    case Difficulty::stype::H:
        validOperators[4] = '%';
        break;
    default:
        break;
    }
    if(this -> newOperators != 0){
       int j = 0;
        for(int i = 10 - this -> newOperators; i < 10; i++){ //add the new operators to the list of allowed ones based on how many are added.
            validOperators[i] = NEWSYMBOLS[j];
            j++;
        } 
    }
}

void Complexity::setDifficulty(Difficulty* difficulty){ //used to set difficulty after creation, not currently used
    this -> difficulty = difficulty;
}

void Complexity::setNoOfOps(int newOperators){ //used to set number of new operators after creation, not currently used
    this -> newOperators = newOperators;
}

std::string Complexity::getEquation(){ //returns a string with a random equation
    std::string returnable = "";
    int segments = this -> difficulty -> getSegments(); //number of numbers in equation
    int magnitude = this -> difficulty -> getMagnitude(); //range that the numbers are allowed to be
    int numbers[segments];
    char symbols[segments - 1];
    for(int i = 0; i < segments; i++){
        if(rand() % 2 == 0){
            numbers[i] = rand() % magnitude; //50% chance to be positive
        } else {
            numbers[i] = -(rand() % magnitude); //50% chance to be negative
        }
    }
    for(int i = 0; i < segments - 1; i++){
        char potential = validOperators[rand() % 10]; //pull an random operator
        if(potential != 'e'){ //make sure the operator chosen is allowed ('e' is the default unset operator, means not allowed operator)
            symbols[i] = potential;
        } else {
            i--; //backstep if bad operator is chosen
        }
    }
    for(int i = 0; i < segments; i++){ //piece the equation together in one string
        if(i == 0){
            returnable += std::to_string(numbers[i]); //set the first number
        } else {
            returnable += ' '; //surround the oprator with spaces and end with a number
            returnable += symbols[i - 1];
            returnable += ' ';
            returnable += std::to_string(numbers[i]);
        }
    }
    return returnable; //return the fully put together equation
}

int Complexity::precedence(char op){ //returns a number, higher the number the earlier in the order of oprations
    if(op == '&'){
        return 1;
    } else if(op == '+' || op == '-' || op == '$'){
        return 2;
    } else if(op == '*' || op == '/' || op == '%' || op == '#'){
        return 3;
    } else if(op == '^' || op == '@'){
        return 4;
    } else {
        return 0;
    }
}

double Complexity::apply(double a, double b, char op){ //returns the number that comes from two numbers and an operators
    switch(op){
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '%':
        return a - b * std::floor(a / b);
    case '^':
        return std::pow(a, b);
    case '&': //definition of new operator &
        return a / (2 * b);
    case '$': //definition of new operator $
        return b * (std::ceil(b / a));
    case '#': //definition of new operator #
        return a + ((3 + a) * b);
    case '@': //definition of new operator @
        return -a - (b * 5);
    }
    return 0;
}

std::string Complexity::solve(std::string equation){ //returns the solution to given equation string
    std::stringstream ss(equation);
    std::vector<std::string> tokens;
    std::string token;

    while(ss >> token){ //tokenize equation
        tokens.push_back(token);
    }

    std::vector<std::string> output; //holds the postfix equation
    std::stack<char> ops;
    for(const std::string& t : tokens){
        if(std::isdigit(t[0]) || (t.size() > 1 && (t[0] == '-' || t[0] == '+'))){ //check if token is a number (preceeding +/- okay)
            output.push_back(t); //put number in output
        } else {
            char op = t[0];

            while(!ops.empty() && precedence(ops.top()) >= precedence(op)){ //pops operators from stack to output if they are earlier in the order of operations
                output.push_back(std::string(1, ops.top()));
                ops.pop();
            }
            ops.push(op); //push current operator to stack
        }
    }
    while(!ops.empty()){ //put any remaining operators in the output
        output.push_back(std::string(1, ops.top()));
        ops.pop();
    }

    std::stack<double> values;
    for(const std::string& t : output){
        if(std::isdigit(t[0]) || (t.size() > 1 && (t[0] == '-' || t[0] == '+'))){ //pushes numbers in the value stack
            values.push(std::stod(t)); //converts string to double
        } else { //its an operator, pop two numbers to use the operator on
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();
            values.push(apply(a, b, t[0])); //put the value back on the stack
        }
    }

    double result = values.top();
    if(result == (int)result){ //convert to int
        return std::to_string((int)result);
    }

    return std::to_string(result); //return the answer if cannot be converted to int
}