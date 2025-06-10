#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <vendor/glm/glm/glm.hpp>

namespace window {
GLFWwindow *init(int width, int height, const char *name);
void configure(GLFWwindow *window);
void terminate();
} // namespace window

#endif