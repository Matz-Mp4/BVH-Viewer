# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

# Directories
SRC_DIR = src
OUT_DIR = out
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin

# Output executable
TARGET = $(BIN_DIR)/volumetric_viewer

# Libraries and includes
LIBS = -lglfw -lGL -ldl -lGLU -lm
INCLUDES = -Iinclude -Iexternal/glad/include -Iexternal/glm

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Create bin and obj directories if they don't exist
$(shell mkdir -p $(BIN_DIR) $(OBJ_DIR))

# Build executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run

