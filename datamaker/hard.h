#pragma once

#include "difficulty.h"

class Hard : public Difficulty{
public:
    int getSegments() const override {return SEGMENTS;}
    int getMagnitude() const override {return MAGNITUDE;}
    int getDifficulty() const {return H;}
private:
    const int SEGMENTS = 5; //5 total numbers
    const int MAGNITUDE = 100; //range -100 - 100 (exclusive)
};