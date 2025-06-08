#include "lighting/light.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <config/glad/glad.h>
#include <string>
   
Light::Light(const glm::vec3& position, const glm::vec3& color)
    : position(position), color(color) {}

void Light::initToShader(Shader& shader, const std::string& uniformName) const 
{
    shader.setVec3(uniformName + "_position", position);
    shader.setVec3(uniformName + "_color", color);
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

void Light::changeXPos(const float val){
    position.x += val;
}

void Light::changeZPos(const float val){
    position.z += val;
}