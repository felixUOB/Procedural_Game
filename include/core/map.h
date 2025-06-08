#ifndef MAP_H
#define MAP_H

#include "core/renderer.h"
#include "graphics/shader.h"
#include "core/gameobj.h"


class Map 
{
    public:
        void load(const std::string& path);
        void render(Renderer& renderer, Shader& shader);
    private:
        std::vector<GameObject> objects;
};

#endif