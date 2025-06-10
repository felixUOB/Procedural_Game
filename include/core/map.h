#ifndef MAP_H
#define MAP_H

#include "core/renderer.h"
#include "graphics/shader.h"
#include "utils/gameobj.h"
#include "tools/shader_manager.h"
#include "tools/mesh_manager.h"


class Map 
{
    public:
        void load(const std::string& path);
        void render(Renderer& renderer, ShaderManager& shaderManager, MeshManager& meshManager, Light& lightCube);
    private:
        std::vector<GameObject> objects;
        std::vector<Light> lights;
};

#endif