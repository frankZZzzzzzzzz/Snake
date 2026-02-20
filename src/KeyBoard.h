#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_set>
#include <thread>
#include <chrono>
#include <functional>
#include <windows.h>

class KeyBoard{
private:
    std::thread keyBoardThread;
    std::unordered_set<char> keysPressed;
    std::function<char(void)> keyInput;
    std::function<void(char)> keyPress;
    std::function<void(char)> keyRelease;
    bool running;
    std::chrono::milliseconds pollTime;

    void threadTask(){
        while (running){
            char key = keyInput();
            if (key != '\0')
                updatePressedKeys(key);

            checkReleasedKeys();
            std::this_thread::sleep_for(pollTime);
        }
    }
    void updatePressedKeys(char key){
        if (keysPressed.find(key) != keysPressed.end())
            return;

        if (keyPress != nullptr)
            keyPress(key);
        keysPressed.insert(key);
    }
    void checkReleasedKeys(){
        for (std::unordered_set<char>::iterator it = keysPressed.begin(); it != keysPressed.end(); it++)
            if (GetAsyncKeyState(*it) == false){
                if (keyRelease != nullptr)
                    keyRelease(*it);
                keysPressed.erase(it);
            }
    }
public:
    ~KeyBoard(){
        if (running){
            running = false;
            keyBoardThread.join();
        }
    }
    KeyBoard(std::function<char(void)> KeyInput, 
    std::function<void(char)> KeyPress, 
    std::function<void(char)> KeyRelease, 
    std::chrono::milliseconds PollTime){
        running = true;
        keyInput = KeyInput;
        keyPress = KeyPress;
        keyRelease = KeyRelease;
        pollTime = PollTime;

        keyBoardThread = std::thread(threadTask,this);
    }
    void end(){
        if (running){
            running = false;
            keyBoardThread.join();
        }
    }
};

#endif