#ifndef TEXTURE_H
#define TEXTURE_H

#include <vendor/glad/glad.h>
#include <string>
#include <vendor/glm/glm/glm.hpp>

class Texture 
{
public:
    static unsigned int LoadTexture(const std::string& path, bool flip = true, bool hasAlpha = false);
};

#endif
