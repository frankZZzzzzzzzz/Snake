CXX = g++
CXXFLAGS = -std=c++23 -MMD -MP

SRC_DIR = src
BUILD_DIR = build

FILES := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(FILES))

SnakeGame.exe: $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf ./$(BUILD_DIR) SnakeGame.exe

#SnakeGame.exe: BuildFolder/Main.o Keyboard.o Layer.o LayerStack.o PollThread.o
#	${CXX} ${CXXFlags} Main.o Keyboard.o Layer.o LayerStack.o PollThread.o -o SnakeGame.exe

#Main.o: src/Main.cpp
#	${CXX} ${CXXFlags} -c $^ ${BuildFolder}$@

#Keyboard.o: src/ControlLayers/Keyboard.cpp src/ControlLayers/Keyboard.h
#	${CXX} ${CXXFlags} -c src/ControlLayers/Keyboard.cpp ${BuildFolder}$@

#Layer.o: src/ControlLayers/Layer.cpp src/ControlLayers/Layer.h
#	${CXX} ${CXXFlags} -c src/ControlLayers/Layer.cpp ${BuildFolder}$@

#LayerStack.o: src/ControlLayers/LayerStack.cpp src/ControlLayers/LayerStack.h
#	${CXX} ${CXXFlags} -c src/ControlLayers/LayerStack.cpp ${BuildFolder}$@

#PollThread.o: src/ControlLayers/PollThread.cpp src/ControlLayers/PollThread.h
#	${CXX} ${CXXFlags} -c src/ControlLayers/PollThread.cpp ${BuildFolder}$@
