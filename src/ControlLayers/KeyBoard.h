#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_set>
#include <thread>
#include <chrono>
#include <functional>
#include <windows.h>
#include <conio.h>

#include "PollThread.h"

class KeyBoard{
private:
    std::unordered_set<char> keysPressed;
    std::function<void(char)> keyPress;
    std::function<void(char)> keyRelease;
    PollThread keyboardThread;

    void threadTask();
    void updatePressedKeys(char key);
    void checkReleasedKeys();
public:
    KeyBoard(std::function<void(char)> KeyPress, 
    std::function<void(char)> KeyRelease = std::function<void(char)>(), 
    int pollRatePerSecond = 10);
    
    ~KeyBoard();
    void end();
};

#endif