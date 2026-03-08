# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 #-Wall -Wextra

# Find all .cpp files recursively in src/
SRCS = $(shell find src -name "*.cpp" ! -name "tempCodeRunnerFile.cpp")

# Convert source filenames to object filenames
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = SnakeGame.exe

# Default target
all: $(TARGET)

# Link objects into the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile .cpp into .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)