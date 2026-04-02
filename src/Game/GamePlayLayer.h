#ifndef GAME_PLAY_LAYER_H
#define GAME_PLAY_LAYER_H

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
#include "Scores/ScoreRecorder.h"

#include "../ControlLayers/Layer.h"

class GamePlayLayer : public Layer{
private:
    std::vector<std::vector<char>> board;
    std::vector<std::pair<int,int>> bodyParts;
    Direction direction;
    ScoreRecorder recorder;
    int boardWidth;
    int boardHeight;
    bool gameOver;

public:
    GamePlayLayer(LayerStack* currStack, int width = 20, int height = 20, bool gameOver = false)
    : Layer(currStack),
    gameOver{gameOver}, boardWidth{width}, boardHeight{height}{

    }
    void run(){
        srand(time(0));
        board = std::vector<std::vector<char>>(boardHeight, std::vector<char>(boardWidth, ' '));
        bodyParts = std::vector<std::pair<int,int>>{{boardHeight/2, boardWidth/2}};
        bodyParts.reserve(boardWidth*boardHeight);
        
        direction = Direction('W');

        placeFruit();
        board[boardHeight/2][boardWidth/2] = 'O';

        while (!gameOver) {
            //std::cout << direction.getCurrDirection() << "\n";
            direction.takeStep();
            moveSnake(std::toupper(direction.getCurrDirection()));
            
            system("cls");
            std::cout << "Fruits Eaten: " << bodyParts.size()-1 << "\n";
            printBoard();
            std::cout << std::endl;
            
            std::this_thread::sleep_for(std::chrono::milliseconds(750));
        }

        if (bodyParts.size() == boardWidth*boardHeight)
            std::cout << "YOU WIN!";
        else
            std::cout << "GAME OVER, YOU LOSE!";
        
        recorder.readScores();
        recorder.addScore(boardWidth,boardHeight,bodyParts.size());
        recorder.saveScores();
        exitLayer();
    }
    void keyPressed(char key){
        key = toupper(key);
        if (bodyParts.size() == 1 && direction.isValidDirection(key)){
            direction.changeDirection(key);
        }
        else if (direction.isValidDirection(key) && direction.isValidDirectionChange(key)){
            direction.changeDirection(key);
        }
    }
    void printBoard() {
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

    void placeFruit() {
        while (true){
            int x = rand() % boardWidth;
            int y = rand() % boardHeight;
            if (board[x][y] == ' ') {
                board[x][y] = 'f';
                break;
            }
        }
    }

    void moveSnake(char direction) {
        std::pair<int,int> head = bodyParts.front();
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
                placeFruit();
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
};

#endif