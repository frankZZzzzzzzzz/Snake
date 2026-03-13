#ifndef LAYER
#define LAYER

#include <forward_list>

#include "LayerStack.h"

class Layer{
private:
    bool running;
protected:
    LayerStack* stack;
public:
    Layer (LayerStack* CurrStack);

    void replaceThisLayer(Layer *otherLayer);
    void exitLayer();
    virtual void keyPressed(char key){};
    virtual void keyReleased(char key){};
    virtual void run() = 0;

    bool isRunning(){
        return(running);
    }
};

#endif