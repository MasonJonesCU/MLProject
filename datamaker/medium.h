#pragma once

#include "difficulty.h"

class Medium : public Difficulty{
public:
    int getSegments() const override {return SEGMENTS;}
    int getMagnitude() const override {return MAGNITUDE;}
    int getDifficulty() const {return M;}
private:
    const int SEGMENTS = 3; //three numbers
    const int MAGNITUDE = 50; //-50 - 50 (exclusive)
};