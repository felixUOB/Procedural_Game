CXX = g++
CXX_FLAGS = -std=c++11 -Wall

CC = gcc
CC_FLAGS = -Wall

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
	src/core/window.cpp \
	src/util/transform.cpp \
	src/core/map.cpp \
	src/tools/shader_manager.cpp

SRC_C = include/vendor/glad.c

OBJ_CPP = $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRC_CPP))
OBJ_C = $(patsubst include/%.c, $(BUILD_DIR)/%.o, $(SRC_C))

GLFW_CFLAGS := $(shell pkg-config --cflags glfw3)
GLFW_LIBS := $(shell pkg-config --libs glfw3)
PROJECT_INCLUDES := -I./include

all: $(TARGET)

# Pattern rule for C++ source files
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXX_FLAGS) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS) -o $@

# Pattern rule for C source files
$(BUILD_DIR)/%.o: include/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CC_FLAGS) -c $< $(PROJECT_INCLUDES) -o $@

# Link all object files into the final executable
$(TARGET): $(OBJ_CPP) $(OBJ_C)
	$(CXX) $^ $(GLFW_LIBS) -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	./$(TARGET)

fresh: clean all run
