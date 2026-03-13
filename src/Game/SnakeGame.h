#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "StartMenu.h"
#include "../ControlLayers/LayerStack.h"

class SnakeGame{
public:
    LayerStack* stack;
    SnakeGame() : stack(new LayerStack()){
        
    }
    ~SnakeGame(){
    }
    void run(){
        StartMenu* menu = new StartMenu(stack);
        stack->addLayer(menu);
        stack->run();
    }
};

#endif