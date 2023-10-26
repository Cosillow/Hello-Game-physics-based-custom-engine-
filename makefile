CXX = g++
CXXFLAGS = -m64 -g -Wall -I include -I imgui
LIBS = -lSDL2 -lSDL2_image

IMGUI_DIR = imgui
IMGUI_SRCS = $(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_OBJS = $(patsubst $(IMGUI_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(IMGUI_SRCS))

SRC_DIR = src
BUILD_DIR = build

# Get all source files in the src directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Generate corresponding object file names in the build directory
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Target executable
TARGET = hellogame.exe

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS) $(IMGUI_OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(IMGUI_OBJS) $(LIBS) -o $@

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build ImGui object files
$(BUILD_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET) $(BUILD_DIR)/imgui.ini

.PHONY: all clean










# CXX = g++
# CXXFLAGS = -m64 -g -Wall -I include
# LIBS = -lSDL2 -lSDL2_image

# SRC_DIR = src
# BUILD_DIR = build

# # Get all source files in the src directory
# SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# # Generate corresponding object file names in the build directory
# OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# # Target executable
# TARGET = game.exe

# # Default target
# all: $(TARGET)

# # Rule to build the executable
# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(OBJS) $(LIBS) -o $@

# # Rule to build object files from source files
# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Clean target to remove generated files
# clean:
# 	rm -f $(BUILD_DIR)/*.o $(TARGET)

# .PHONY: all clean
