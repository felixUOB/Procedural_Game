#ifndef MAP_H
#define MAP_H

#include "core/renderer.h"
#include "graphics/shader.h"
#include "core/gameobj.h"
#include "tools/shader_manager.h"


class Map 
{
    public:
        void load(const std::string& path);
        void render(Renderer& renderer, ShaderManager& shaderManager, Light& lightCube, Mesh& cubeMesh);
    private:
        std::vector<GameObject> objects;
};

#endif