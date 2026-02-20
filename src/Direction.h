#ifndef KEYPRESSCHECKER_H
#define KEYPRESSCHECKER_H

#include <functional>

class Direction{
private:
    std::function<bool(char,char)> validDirectionChange;
    std::function<bool(char)> validDirection;
    char nextDirection;
    char currDirection;

public:
    Direction(char startingDirection = 'W', std::function<bool(char,char)> validDirectionChange = nullptr, std::function<bool(char)> validDirection = nullptr) 
    : nextDirection(startingDirection), 
    currDirection(startingDirection), 
    validDirectionChange(validDirectionChange),
    validDirection(validDirection)
    {}

    char getCurrDirection(){
        return (currDirection);
    }
    void changeDirection(char direction){
        nextDirection = direction;
    }
    void takeStep(){
        currDirection = nextDirection;
    }
    bool isValidDirection(char direction){
        if (validDirection == nullptr)
            return (true);
        return (validDirection(direction));
    }
    bool isValidDirectionChange(char direction){
        if (validDirectionChange == nullptr)
            return (true);
        return (validDirectionChange(direction,currDirection));
    }
};

#endif