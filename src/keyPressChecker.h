#ifndef KEYPRESSCHECKER_H
#define KEYPRESSCHECKER_H

#include <unordered_set>
#include <forward_list>

class keyPressChecker{
private:
    char lastKey;
    std::unordered_set<char> keysPressed;
    std::forward_list<char> order;
public:
    keyPressChecker(char defaultKey = 'W') : lastKey(defaultKey) {
    }
    char getRecentKey(){
        return (lastKey);
    }
    void keyRelease(char key) {
        keysPressed.extract(key);
        order.remove(key);
        
        if (!order.empty())
            lastKey = order.front();
    }
    void keyPress(char key) {
        keysPressed.insert(key);
        order.push_front(key);
        lastKey = order.front();
    }
    std::forward_list<char> getOrderKeysPressed(){
        return order;
    }
    bool isKeyPressed(char key) {
        return(keysPressed.find(key) != keysPressed.end());
    }
};

#endif