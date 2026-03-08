#ifndef SCORE_H
#define SCORE_H

#include <utility>
#include <string>
#include <iostream>
#include <time.h>

class Score{
private:
    time_t date;
    int width;
    int height;
    int finalLength;
public:
    Score(){

    }
    Score(int Width, int Height, time_t Date, int Length){
        width = Width;
        height = Height;
        date = Date;
        finalLength = Length;
    }
    
    void setBoardSize(int Width, int Height){
        width = Width;
        height = Height;
    }
    void setBoardSize(std::string size){
        int xIndex = size.find('x');
        width = std::stoi(size.substr(0,xIndex));
        height = std::stoi(size.substr(xIndex));
    }
    void setDate(time_t Date){
        date = Date;
    }
    void setLength(int Length){
        finalLength = Length;
    }
    friend std::ostream& operator<<(std::ostream& out, Score score);

};
std::ostream& operator<<(std::ostream& out, Score score){
    out << ctime(&score.date) << " " << score.width << "x" << score.height << " Length: " << score.finalLength;
    return (out);
}

#endif