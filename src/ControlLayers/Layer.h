#ifndef LAYER
#define LAYER

#include <forward_list>

#include "LayerStack.h"

class Layer{
public:
    bool isTransparent;
    
    Layer (bool isTransparent = false);

    void replaceThisLayer(Layer *otherLayer);
    void exitLayer();
    virtual void keyPressed(char key){};
    virtual void keyReleased(char key){};
    virtual void run() = 0;
};

#endif