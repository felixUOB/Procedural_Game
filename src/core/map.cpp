#include "core/map.h"
#include "core/renderer.h"
#include "graphics/shader.h"

void Map::load(const std::string& path)
{
    // Load JSON data from map file and assign gameObjects of corresponding type (cubeObject etc)
}

void Map::render(Renderer& renderer, Shader& shader)
{
    //  // 1. Use cube shader and render all cubes
    // cubeShader.use();
    // for (const GameObject& obj : cubeObjects) {
    //     obj.Render(renderer, cubeShader);
    // }

    // // 2. Use light source shader and render lights
    // lightShader.use();
    // for (const LightObject& light : lights) {
    //     light.Render(renderer, lightShader);
    // }

    // // 3. Repeat for other shaders/materials...
}
