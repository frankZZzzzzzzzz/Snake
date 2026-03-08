#ifndef DIRECTION_H
#define DIRECTION_H

#include <functional>

class Direction{
private:
    char nextDirection;
    char currDirection;
public:
    Direction(char startingDirection = 'W') 
    : nextDirection(startingDirection), 
    currDirection(startingDirection)
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
    
    bool isValidDirection(char newDirection){
        return (newDirection == 'W' || newDirection == 'A' || newDirection == 'S' || newDirection == 'D');
    }
    
    bool isValidDirectionChange(char newDirection){
        return !(newDirection == 'W' && currDirection == 'S' ||
            newDirection == 'A' && currDirection == 'D' ||
            newDirection == 'S' && currDirection == 'W' ||
            newDirection == 'D' && currDirection == 'A');
    }
};

#endif