#ifndef SCORE_RECOREDER_H
#define SCORE_RECOREDER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <ctime>
#include <map>

#include "Score.h"

class ScoreRecorder{
private:
    std::string fileName;
    std::vector<Score> scores;
public:
    ScoreRecorder(std::string fileName = "Scores.txt"){
        this->fileName = fileName;
    }
    void addScore(int boardWidth, int boardHeight, int snakeLength){
        scores.insert(scores.begin(),Score(time(0),boardWidth, boardHeight, snakeLength));
    }
    void addScore(Score score){
        scores.insert(scores.begin(),score);
    }
    void createSaveFile(){
        std::ofstream file(fileName);
        if (!file.is_open()){
            throw std::ios_base::failure("Save File Cannot be Created");
        }
        file.close();
    }
    void readScores(){
        std::ifstream file(fileName);
        std::vector<Score> scores;
        if (!file.is_open()){
            createSaveFile();
            return;
        }
        std::string currLine;
        while (std::getline(file,currLine)){
            Score currScore;
            std::stringstream ss(currLine);
            std::string token;

            ss >> token;
            currScore.setDate(std::stol(token));
            ss >> token;
            currScore.setBoardSize(token);
            ss >> token;
            currScore.setLength(std::stoi(token));
            scores.push_back(currScore);
        }

        file.close();
    }
    void saveScores(){
        std::ofstream file(fileName);
        if (!file.is_open()){
            throw std::ios_base::failure("Save File Cannot be Created");
        }
        for (Score score : scores){
            file << score << "\n";
        }
        file.close();
    }
};

#endif