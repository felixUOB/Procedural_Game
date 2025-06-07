#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>
#include <glm/glm/glm.hpp>

class Texture 
{
public:
    static unsigned int LoadTexture(const std::string& path, bool flip = true, bool hasAlpha = false);
};

#endif
