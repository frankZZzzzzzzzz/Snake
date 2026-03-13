#include "Layer.h"

Layer::Layer (LayerStack* CurrStack)
: stack{CurrStack}{
    running = true;
}
void Layer::replaceThisLayer(Layer *otherLayer){
    stack->replaceLayer(otherLayer);
}
void Layer::exitLayer(){
    running = false;
}
