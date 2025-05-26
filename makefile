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

$(OBJ_CPP): $(SRC_CPP)
	$(CXX) -c $< $(PROJECT_INCLUDES) $(GLFW_CFLAGS)

$(OBJ_C): $(SRC_C)
	$(CC) -c $< $(PROJECT_INCLUDES)

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
