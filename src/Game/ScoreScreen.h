#include <vector>
#include <iostream>

#include "../ControlLayers/LayerStack.h"
#include "../ControlLayers/Layer.h"
#include "Scores/ScoreRecorder.h"
#include "Scores/Score.h"

class ScoreScreen : public Layer{
private:
    ScoreRecorder recorder;
    std::vector<Score> allScores;
public:
    ScoreScreen(LayerStack* currStack) : Layer(currStack){
        recorder.readScores();
        allScores = recorder.getAllScores();
    }
    void run(){
        system("cls");
        std::cout << "Scores: (Press 1 to exit)" << std::endl;
        for (int i = 0; i < allScores.size() && i < 10; i++){
            std::cout << i << ") " << allScores[i] << std::endl;
        }
    }
    void keyPressed(char key){
        if (key == '1')
            exitLayer();
    }
};