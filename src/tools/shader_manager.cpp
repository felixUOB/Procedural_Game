#include "tools/shader_manager.h"
#include <iostream>
#include <unordered_map>

void ShaderManager::registerShader(const std::string &name, Shader &shader) {
  std::cout << "Registering Shader: " << name << std::endl;
  shaders.emplace(name, shader);
}

Shader &ShaderManager::get(const std::string &name) { return shaders.at(name); }