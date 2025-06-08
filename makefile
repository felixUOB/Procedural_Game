CXX = g++
CXX_FLAGS = -std=c++11

CC = clang
TARGET = game.exe
BUILD_DIR = build

SRC_CPP = \
    src/main.cpp \
    src/graphics/shader.cpp \
    src/graphics/texture.cpp \
    src/camera/camera.cpp \
    src/lighting/light.cpp \
	src/graphics/mesh.cpp \
	src/core/renderer.cpp \
	src/core/geometry.cpp \
	src/core/timer.cpp \
	src/core/window.cpp

SRC_C = src/glad.c

OBJ_CPP = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRC_CPP))
OBJ_C = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRC_C))

GLFW_CFLAGS := $(shell pkg-config --cflags glfw3)
GLFW_LIBS := $(shell pkg-config --libs glfw3)
PROJECT_INCLUDES := -I./include

all: $(TARGET)

# Pattern rule for C++ source files
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS) -o $@

# Pattern rule for C source files
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< $(PROJECT_INCLUDES) -o $@

# Link all object files into the final executable
$(TARGET): $(OBJ_CPP) $(OBJ_C)
	$(CXX) $^ $(GLFW_LIBS) -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)

fresh: clean all run
