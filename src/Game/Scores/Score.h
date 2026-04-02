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
    Score(int Width, int Height, time_t Date, int Length);
    Score(const Score& other);
    void setBoardSize(int Width, int Height);
    void setBoardSize(std::string size);
    void setDate(time_t Date);
    void setLength(int Length);
    friend std::ostream& operator<<(std::ostream& out, Score score);
};
std::ostream& operator<<(std::ostream& out, Score score){
    out << ctime(&score.date) << " " << score.width << "x" << score.height << " Length: " << score.finalLength;
    return (out);
}

#endif