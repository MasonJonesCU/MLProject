#pragma once

#include "difficulty.h"
#include <string>

class Complexity{
public:
    Complexity(Difficulty*, int newOperators = 1);
    std::string getEquation();
    std::string solve(std::string);
    void setDifficulty(Difficulty*);
    void setNoOfOps(int);
    char validOperators[10] = {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'};
private:
    double apply(double a, double b, char op);
    int precedence(char op);
    Difficulty* difficulty = nullptr;
    int newOperators;
    int random;
    const char NEWSYMBOLS[4] = {'&', '$', '#', '@'};
};