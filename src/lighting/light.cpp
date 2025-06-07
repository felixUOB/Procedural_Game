#include "lighting/light.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <config/glad/glad.h>
#include <string>
   
Light::Light(Type type, const glm::vec3& position, const glm::vec3& color)
    : type(type), position(position), color(color) {}

void Light::applyToShader(Shader& shader, const std::string& uniformName) const 
{
    shader.setVec3(uniformName + ".position", position);
    shader.setVec3(uniformName + ".color", color);
}

const glm::vec3& Light::getPosition() const {
    return position;
}

const glm::vec3& Light::getColor() const {
    return color;
}

void Light::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Light::setColor(const glm::vec3& col) {
    color = col;
}