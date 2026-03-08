#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <forward_list>
#include <thread>
#include <chrono>
#include <memory>
#include <atomic>

// Forward declarations to avoid circular includes
class Layer;
class KeyBoard;
class PollThread;

class LayerStack {
private:
    static std::forward_list<Layer*> LayerOrder;
    static std::unique_ptr<KeyBoard> keyboard;
    static std::chrono::milliseconds pollPeriod;
    static std::atomic<bool> running;
    static bool isInit;
public:
    static void init(bool haveKeyboardInputs = true, int RefreshPerSecond = 1, int keyboardRefreshPerSecond = 20);
    static void shutdown();

    static void addLayer(Layer* layer);
    static void deleteLayer(Layer* layer);
    static void replaceLayer(Layer* layer);

    static void keyPressed(char key);
    static void keyReleased(char key);
    static void runStack();

    static bool isRunning();
};

#endif // LAYER_STACK_H