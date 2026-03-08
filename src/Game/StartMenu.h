#ifndef START_MENU_H
#define START_MENU_H

#include <iostream>

#include "../ControlLayers/Layer.h"
#include "../ControlLayers/LayerStack.h"
#include "GamePlayLayer.h"

class StartMenu : public Layer{
public:
    StartMenu(){
    }
    void run(){
        system("cls");
        std::cout << "(1) Start\t(2) Settings\t(3) Previous Scores\n";
    }
    void keyPressed(char key){
        switch(key){
            case '1': LayerStack::addLayer(new GamePlayLayer()); break;
            case '2': LayerStack::addLayer(new GamePlayLayer()); break;
            case '3': 
                LayerStack::shutdown();
                exit(0);
            default: return;
        }
    }
};

#endif
