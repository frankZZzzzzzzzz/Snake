#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <list>
#include <thread>
#include <chrono>
#include <conio.h>
#include <cctype>

#include "keyPressChecker.h"


keyPressChecker keyChecker('W');
bool gameOver = false;

void printBoard(std::vector<std::vector<char>>& board) {
    for (int i = 0; i < board.size()+2; i++) {
        std::cout << "*";
    }
    std::cout << "\n";

    for (std::vector<char> &row : board){
        std::cout << "*";
        for (char c : row) {
            std::cout << c;
        }
        std::cout << "*\n";
    }

    for (int i = 0; i < board.size()+2; i++) {
        std::cout << "*";
    }
    std::cout << "\n";
}

void placeFruit(std::vector<std::vector<char>>& board) {
    while (true){
        int x = rand() % board.size();
        int y = rand() % board[0].size();
        if (board[x][y] == ' ') {
            board[x][y] = 'f';
            break;
        }
    }
}

void moveSnake(std::vector<std::vector<char>>& board, std::list<std::pair<int,int>>& bodyParts, char direction) {
    std::pair<int,int> head = bodyParts.front();
    std::pair<int,int> newHead = head;

    switch (direction) {
        case 'W': newHead.first = (newHead.first - 1 + board.size()) % board.size(); break;
        case 'S': newHead.first = (newHead.first + 1) % board.size(); break;
        case 'A': newHead.second = (newHead.second - 1 + board[0].size()) % board[0].size(); break;
        default/*D*/: newHead.second = (newHead.second + 1) % board[0].size(); break;
    }

    if (board[newHead.first][newHead.second] == 'o') {
        gameOver = true;
        std::cout << "Game Over!" << std::endl;
    }
    else if (board[newHead.first][newHead.second] == 'f') {
        bodyParts.push_front(newHead);
        board[head.first][head.second] = 'o';
        board[newHead.first][newHead.second] = 'O';

        if (bodyParts.size() == board.size() * board[0].size()) {
            gameOver = true;
            std::cout << "You Win!" << std::endl;
        }
        else {
            placeFruit(board);
        }
    }
    else{
        bodyParts.push_front(newHead);
        board[newHead.first][newHead.second] = 'O';

        if (bodyParts.size() > 1) 
            board[head.first][head.second] = 'o';

        board[bodyParts.back().first][bodyParts.back().second] = ' ';
        bodyParts.pop_back();
    }
}

void checkKeyPress() {
    if (_kbhit()) {
        std::cout << "Key Pressed\n";
        char key = std::toupper(char(_getch()));
        if (key != keyChecker.getRecentKey())
            keyChecker.keyPress(key);
    }
}

int main(){
    std::thread keyboardThread([](){
        while (!gameOver) {
            checkKeyPress();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });
    int boardSize = 20;
    std::vector<std::vector<char>> board(boardSize, std::vector<char>(boardSize, ' '));
    std::list<std::pair<int,int>> bodyParts{{boardSize/2, boardSize/2}};

    placeFruit(board);
    board[boardSize/2][boardSize/2] = 'O';

    while (!gameOver) {
        char direction = keyChecker.getRecentKey();
        std::cout << keyChecker.getRecentKey() << "\n";
        moveSnake(board, bodyParts, std::toupper(direction));
        
        system("cls");
        printBoard(board);
        std::cout << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }
    keyboardThread.join();
}