#ifndef START_MENU_H
#define START_MENU_H

#include <iostream>

#include "../ControlLayers/Layer.h"
#include "../ControlLayers/LayerStack.h"
#include "GamePlayLayer.h"
#include "ScoreScreen.h"

class StartMenu : public Layer{
public:
    StartMenu(LayerStack* currStack) : Layer(currStack){
    }
    void run(){
        system("cls");
        std::cout << "(1) Start\t(2) Previous Scores\t(3) Exit\n";
    }
    void keyPressed(char key){
        switch(key){
            case '1': stack->addLayer(new GamePlayLayer(stack)); break;
            case '2': stack->addLayer(new ScoreScreen(stack)); break;
            case '3': exitLayer(); break;
            default: return;
        }
    }
};

#endif
