#include "LayerStack.h"
#include "Layer.h"   
#include "KeyBoard.h"
#include "PollThread.h"

std::unique_ptr<KeyBoard> LayerStack::keyboard = nullptr;
std::forward_list<Layer*> LayerStack::LayerOrder;
std::chrono::milliseconds LayerStack::pollPeriod;
std::atomic<bool> LayerStack::running = false;
bool LayerStack::isInit = false;

// ---------------- Public ----------------
void LayerStack::init(bool haveKeyboardInputs, int RefreshPerSecond, int keyboardRefreshPerSecond) {
    if (isInit)
        return;

    isInit = true;
    if (haveKeyboardInputs) {
        keyboard = std::make_unique<KeyBoard>(keyPressed, keyReleased, keyboardRefreshPerSecond);
    }
}

void LayerStack::shutdown() {
    isInit = false;
    for (Layer* layer : LayerOrder)
        delete layer;
    LayerOrder.clear();
    keyboard->end();
}

void LayerStack::addLayer(Layer* layer) {
    LayerOrder.push_front(layer);
    if (!LayerStack::isInit){
        LayerStack::init();
        LayerStack::runStack();
    }
}

void LayerStack::deleteLayer(Layer* layer) {
    auto prev = LayerOrder.before_begin();
    auto curr = LayerOrder.begin();

    while (curr != LayerOrder.end()) {
        if (*curr == layer) {
            delete *curr;
            LayerOrder.erase_after(prev);
            break;
        }
        ++prev;
        ++curr;
    }
}

void LayerStack::replaceLayer(Layer* layer) {
    if (!LayerOrder.empty()) {
        Layer* previousLayer = LayerOrder.front();
        LayerOrder.front() = layer;
        delete previousLayer;
    } else {
        addLayer(layer);
    }
}

void LayerStack::keyPressed(char key) {
    if (!LayerOrder.empty())
        LayerOrder.front()->keyPressed(key);
}

void LayerStack::keyReleased(char key) {
    if (!LayerOrder.empty())
        LayerOrder.front()->keyReleased(key);
}

void LayerStack::runStack() {
    running = true;
    while (true){
        auto it = LayerOrder.begin();
        while (it != LayerOrder.end()) {
            (*it)->run();
            ++it;
        }
        if (it != LayerOrder.end())
            (*it)->run();

        auto later = std::chrono::steady_clock::now() + std::chrono::seconds(2);
        std::this_thread::sleep_until(later);
    }
}
bool LayerStack::isRunning(){
    return(running);
}