#include <iostream>
#include <vector>
#include <utility>
#include <thread>
#include <chrono>
#include <conio.h>
#include <cctype>
#include <cstdlib>
#include <functional>
#include <ctime>

#include "Direction.h"
#include "KeyBoard.h"

bool gameOver = false;

bool isValidDirectionChange(char newDirection, char currDirection);
bool isValidDirection(char newDirection);

bool isValidDirectionChange(char newDirection, char currDirection){
    return !(newDirection == 'W' && currDirection == 'S' ||
            newDirection == 'A' && currDirection == 'D' ||
            newDirection == 'S' && currDirection == 'W' ||
            newDirection == 'D' && currDirection == 'A');
}
bool isValidDirection(char newDirection){
    if (newDirection != 'W' && newDirection != 'A' && newDirection != 'S' && newDirection != 'D')
        return (false);
    return (true);
}

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

void moveSnake(std::vector<std::vector<char>>& board,std::vector<std::pair<int,int>>& bodyParts, char direction) {
    std::pair<int,int> head = *bodyParts.begin();
    std::pair<int,int> newHead = head;

    switch (direction) {
        case 'W': newHead.first = (newHead.first - 1 + board.size()) % board.size(); break;
        case 'S': newHead.first = (newHead.first + 1) % board.size(); break;
        case 'A': newHead.second = (newHead.second - 1 + board[0].size()) % board[0].size(); break;
        case 'D': newHead.second = (newHead.second + 1) % board[0].size(); break;
    }

    if (board[newHead.first][newHead.second] == 'o' && newHead != bodyParts.back()) {
        gameOver = true;
    }
    else if (board[newHead.first][newHead.second] == 'f') {
        bodyParts.insert(bodyParts.begin(),newHead);
        board[head.first][head.second] = 'o';
        board[newHead.first][newHead.second] = 'O';

        if (bodyParts.size() == board.size() * board[0].size()) {
            gameOver = true;
        }
        else {
            placeFruit(board);
        }
    }
    else{
        board[bodyParts.back().first][bodyParts.back().second] = ' ';
        bodyParts.pop_back();

        bodyParts.insert(bodyParts.begin(),newHead);
        board[newHead.first][newHead.second] = 'O';

        if (bodyParts.size() > 1) 
            board[head.first][head.second] = 'o';

    }
}

char keyBoardInput(){
    if (!_kbhit())
        return ('\0');

    return (std::toupper(char(_getch())));
}

int main(){
    srand(time(0));
    int boardSize = 20;

    std::vector<std::vector<char>> board(boardSize, std::vector<char>(boardSize, ' '));
    std::vector<std::pair<int,int>> bodyParts{{boardSize/2, boardSize/2}};
    bodyParts.reserve(boardSize*boardSize);
    
    Direction direction('W',isValidDirectionChange, isValidDirection);
    
    std::function<char(void)> keyBoardInput = []() -> char{
        if (!_kbhit())
            return ('\0');

        return (std::toupper(char(_getch())));
    };
  
    std::function<void(char)> keyPressed = [&bodyParts, &direction](char key){
        if (bodyParts.size() == 1 && direction.isValidDirection(key))
            direction.changeDirection(key);
        else if (direction.isValidDirection(key) && direction.isValidDirectionChange(key))
            direction.changeDirection(key);
    };

    KeyBoard keyboard(keyBoardInput,keyPressed,nullptr,std::chrono::milliseconds(10));

    placeFruit(board);
    board[boardSize/2][boardSize/2] = 'O';

    while (!gameOver) {
        std::cout << direction.getCurrDirection() << "\n";
        direction.takeStep();
        moveSnake(board, bodyParts, std::toupper(direction.getCurrDirection()));
        
        system("cls");
        std::cout << "Fruits Eaten: " << bodyParts.size()-1 << "\n";
        printBoard(board);
        std::cout << std::endl;
        
        std::this_thread::sleep_for(std::chrono::milliseconds(750));
    }
    keyboard.end();

    if (bodyParts.size() == boardSize*boardSize)
        std::cout << "YOU WIN!";
    else
        std::cout << "GAME OVER, YOU LOSE!";
    
    std::cin.get();
}