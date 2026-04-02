#include "Score.h"

Score::Score(int Width, int Height, time_t Date, int Length){
    width = Width;
    height = Height;
    date = Date;
    finalLength = Length;
}
Score::Score(const Score& other){
    width = other.width;
    height = other.height;
    date = other.date;
    finalLength = other.finalLength;
}
void Score::setBoardSize(int Width, int Height){
    width = Width;
    height = Height;
}
void Score::setBoardSize(std::string size){
    int xIndex = size.find('x');
    width = std::stoi(size.substr(0,xIndex));
    height = std::stoi(size.substr(xIndex));
}
void Score::setDate(time_t Date){
    date = Date;
}
void Score::setLength(int Length){
    finalLength = Length;
}
std::ostream& operator<<(std::ostream& out, Score score){
    out << ctime(&score.date) << " " << score.width << "x" << score.height << " Length: " << score.finalLength;
    return (out);
}