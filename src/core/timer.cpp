#include "core/timer.h"
#include <GLFW/glfw3.h>

void Timer::update() {
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}