#include "core/map.h"
#include "core/renderer.h"
#include "graphics/shader.h"
#include "tools/shader_manager.h"

#include <fstream>
#include <iostream>
#include <tools/json.hpp>
#include <fstream>

void Map::load(const std::string& path)
{
    std::cout << "Loading Map from:" <<  path << std::endl;
    nlohmann::json mapData;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open JSON file!" << std::endl;
        return;
    }

    file >> mapData;
    std::cout << mapData << std::endl;
}

void Map::render(Renderer& renderer, ShaderManager& shaderManager)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
