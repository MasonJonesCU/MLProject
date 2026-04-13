#pragma once

#include "difficulty.h"

class Easy : public Difficulty{
public:
    int getSegments() const override {return SEGMENTS;}
    int getMagnitude() const override {return MAGNITUDE;}
    int getDifficulty() const {return E;}
private:
    const int SEGMENTS = 2; //only two numbers
    const int MAGNITUDE = 10; //range -10 - 10 (exclusive)
};