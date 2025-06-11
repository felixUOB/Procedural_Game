#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "graphics/shader.h"
#include <unordered_map>

class ShaderManager {
public:
  void registerShader(const std::string &name, Shader &shader);
  Shader &get(const std::string &name);

private:
  std::unordered_map<std::string, Shader> shaders;
};

#endif