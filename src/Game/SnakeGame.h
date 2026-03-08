#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "StartMenu.h"
#include <iostream>

class SnakeGame{
public:
    SnakeGame(){
    }
    ~SnakeGame(){
        LayerStack::shutdown();
    }
    void run(){
        StartMenu* menu = new StartMenu();
        LayerStack::addLayer(menu);
        std::cout << "DONE\n";
    }
};

#endif