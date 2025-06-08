#include "tools/shader_manager.h"
#include <unordered_map>
#include <stdio.h>
#include <iostream>




void ShaderManager::registerShader(const char* name, Shader& shader)
{
    std::cout << "Registering Shader: " << name << std::endl;
    shaders.insert({name, shader});
}

Shader& ShaderManager::get(const std::string& name) 
{
    return shaders.at(name);
}