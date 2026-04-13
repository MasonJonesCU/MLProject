#pragma once

class Difficulty{ //implemented with Easy, Medium, and Hard
public:
    Difficulty(){}
    virtual ~Difficulty(){}
    virtual int getSegments() const = 0;
    virtual int getMagnitude() const = 0;
    virtual int getDifficulty() const = 0;
    enum stype{
        E,
        M,
        H
    };
};