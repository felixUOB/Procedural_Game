#include "tools/shader_manager.h"
#include <iostream>
#include <unordered_map>

void ShaderManager::registerShader(const char *name, Shader &shader) {
  std::cout << "Registering Shader: " << name << std::endl;
  shaders.insert({name, shader});
}

Shader &ShaderManager::get(const std::string &name) { return shaders.at(name); }