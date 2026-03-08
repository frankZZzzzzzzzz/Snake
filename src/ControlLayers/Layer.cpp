#include "Layer.h"

Layer::Layer (bool isTransparent): isTransparent{isTransparent}{
}
void Layer::replaceThisLayer(Layer *otherLayer){
    LayerStack::replaceLayer(otherLayer);
}
void Layer::exitLayer(){
    LayerStack::deleteLayer(this);
}
