#ifndef WINDOW_H
#define WINDOW_H

#include <config/glm/glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace window {
    GLFWwindow* init(int width, int height, const char* name);
    void configure(GLFWwindow* window);
    void terminate();
}

#endif