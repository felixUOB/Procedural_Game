CXX = g++
CC = clang
TARGET = engine.exe 

SRC_CPP = src/main.cpp
SRC_C = src/glad.c

OBJ_CPP = main.o
OBJ_C = glad.o

GLFW_CFLAGS := $(shell pkg-config --cflags glfw3)
GLFW_LIBS := $(shell pkg-config --libs glfw3)
PROJECT_INCLUDES := -I./include

all: $(TARGET)

# Compile each .cpp to .o
%.o: src/%.cpp
	$(CXX) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS) -o $@

# Special rules for .cpp files in subfolders:
shader.o: src/graphics/shader.cpp
	$(CXX) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS) -o $@

texture.o: src/graphics/texture.cpp
	$(CXX) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS) -o $@

camera.o: src/game/camera.cpp
	$(CXX) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS) -o $@

# Compile C source files
%.o: src/%.c
	$(CC) -c $< $(PROJECT_INCLUDES) -o $@

$(TARGET): $(OBJ_CPP) $(OBJ_C)
	$(CXX) $^ $(GLFW_LIBS) -o $@

clean:
	rm -f $(OBJ_CPP) $(OBJ_C) $(TARGET)

run:
	make
	./engine.exe

fresh:
	make clean
	make
	./engine.exe
