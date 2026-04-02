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
    ScoreRecorder(std::string fileName = "Scores.txt");
    void addScore(int boardWidth, int boardHeight, int snakeLength);
    void addScore(Score score);
    void createSaveFile();
    void readScores();
    void saveScores();
    const std::vector<Score>& getAllScores(){
        return (scores);
    }
};

#endif