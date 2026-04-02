#include "ScoreRecorder.h"

ScoreRecorder::ScoreRecorder(std::string fileName){
    this->fileName = fileName;
}
void ScoreRecorder::addScore(int boardWidth, int boardHeight, int snakeLength){
    scores.insert(scores.begin(),Score(time(0),boardWidth, boardHeight, snakeLength));
}
void ScoreRecorder::addScore(Score score){
    scores.insert(scores.begin(),score);
}
void ScoreRecorder::createSaveFile(){
    std::ofstream file(fileName);
    if (!file.is_open()){
        throw std::ios_base::failure("Save File Cannot be Created");
    }
    file.close();
}
void ScoreRecorder::readScores(){
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
void ScoreRecorder::saveScores(){
    std::ofstream file(fileName);
    if (!file.is_open()){
        throw std::ios_base::failure("Save File Cannot be Created");
    }
    for (Score score : scores){
        file << score << "\n";
    }
    file.close();
}