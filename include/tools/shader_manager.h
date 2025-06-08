#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <unordered_map>
#include "graphics/shader.h"


class ShaderManager {
public:
    void registerShader(const char* name, Shader& shader);
    Shader& get(const std::string& name);

private:
    std::unordered_map<std::string, Shader> shaders;
};


#endif 