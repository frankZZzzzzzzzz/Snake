#include <fstream>

class ScoreSaver{
private:
    std::string fileName = "Scores.txt";
public:
    void createSaveFile(){
        std::ofstream file(fileName);
        if (!file.is_open()){
            throw new std::exception("Save File Cannot be Created");
        }
        file.close();
    }
    void readScores(){
        std::ifstream file(fileName);
        if (!file.is_open()){
            createSaveFile();
            return;
        }
        
    }
    void saveScores(){
        std::ofstream file(fileName);
        if (!file.is_open()){
            throw new std::exception("Save File Cannot be Created");
        }
        file.
        file.close();
    }
};