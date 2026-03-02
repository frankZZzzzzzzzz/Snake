#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <map>

#include "Score.h"

class ScoreSaver{
private:
    std::string fileName;
    std::vector<Score> scores;
public:
    ScoreSaver(std::string fileName = "Scores.txt"){
        this->fileName = fileName;
    }
    void addScore(Score score){
        scores.insert(scores.begin(),score);
    }
    void createSaveFile(){
        std::ofstream file(fileName);
        if (!file.is_open()){
            throw new std::exception("Save File Cannot be Created");
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
            throw new std::exception("Save File Cannot be Created");
        }
        for (Score score : scores){
            file << score << "\n";
        }
        file.close();
    }
};