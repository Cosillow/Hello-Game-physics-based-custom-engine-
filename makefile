IMGUI_DIR = lib/imgui
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

ifeq ($(os),windows)
TARGET ?= bin/hellogame.exe

CXX := x86_64-w64-mingw32-g++
CXXFLAGS := --std=c++17 -g -Wall -Wextra -w -fpermissive -I $(INCLUDE_DIR) -I $(IMGUI_DIR) -I/usr/local/x86_64-w64-mingw32/include
LDFLAGS := -static -static-libgcc
LIBS := $(shell /usr/local/x86_64-w64-mingw32/bin/sdl2-config --static-libs) -lSDL2_image
else
TARGET ?=bin/hellogame.out

CXX := g++
CXXFLAGS := --std=c++17 -m64 -g -Wall -Wextra -I $(INCLUDE_DIR) -I $(IMGUI_DIR) -MMD
LDFLAGS :=
LIBS := -lSDL2 -lSDL2_image
endif

IMGUI_SRCS = $(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_OBJS = $(patsubst $(IMGUI_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(IMGUI_SRCS))


# Get all source files in the src directory
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# Generate corresponding object file names in the build directory
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
.PHONY: all
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS) $(IMGUI_OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(IMGUI_OBJS) -o $@ $(LIBS)

# Rule to build object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build ImGui object files
$(BUILD_DIR)/%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	

# Include automatically generated dependencies
-include $(BUILD_DIR)/*.d

# Target to build and run the executable
.PHONY: run
run: $(TARGET)
	./$(TARGET)

# Clean target to remove generated files
.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.o $(BUILD_DIR)/*.d $(TARGET) $(BUILD_DIR)/imgui.ini
