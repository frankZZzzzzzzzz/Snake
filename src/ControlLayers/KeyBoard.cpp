#include "KeyBoard.h"

KeyBoard::KeyBoard(std::function<void(char)> KeyPress, 
    std::function<void(char)> KeyRelease, 
    int pollRatePerSecond) :
    keyPress{KeyPress},
    keyRelease{KeyRelease},
    keyboardThread(pollRatePerSecond, threadTask,this/*[this](){this->threadTask();}*/){
}

KeyBoard::~KeyBoard(){
    keyboardThread.join();
}
void KeyBoard::end(){
    keyboardThread.join();
}

void KeyBoard::threadTask(){
    char key = '\0';
    while (_kbhit()){
        key = _getch();
        updatePressedKeys(key);
    }

    checkReleasedKeys();
}
void KeyBoard::updatePressedKeys(char key){
    if (keysPressed.find(key) != keysPressed.end())
        return;

    if (keyPress)
        keyPress(key);
    keysPressed.insert(key);
}
void KeyBoard::checkReleasedKeys(){
    std::unordered_set<char>::iterator it = keysPressed.begin();
    while (it != keysPressed.end()){
        if (GetAsyncKeyState(*it) == false){
            if (keyRelease != nullptr)
                keyRelease(*it);
            it = keysPressed.erase(it);
        }
        else
            it++;
    }
}