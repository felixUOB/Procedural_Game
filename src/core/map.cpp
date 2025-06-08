#include "core/map.h"
#include "core/renderer.h"
#include "graphics/shader.h"
#include "tools/shader_manager.h"
#include "tools/mesh_manager.h"
#include <fstream>
#include <iostream>
#include <vendor/json.hpp>
#include <fstream>

#include <vendor/glad/glad.h>
#include <GLFW/glfw3.h>
#include <vendor/glm/glm/glm.hpp>
#include <vendor/glm/glm/gtc/matrix_transform.hpp>
#include <vendor/glm/glm/gtc/type_ptr.hpp>

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

void Map::render(Renderer& renderer, ShaderManager& shaderManager, MeshManager& meshManager, Light& lightCube)
{

    // 1. Render Crates
    Shader currentShader = shaderManager.get("cubeLightingShader");
    currentShader.use();

    Transform temp;
    float time = glfwGetTime();

    temp.scale = glm::vec3(1.0f, 1.0f, 1.0f);
    temp.rotation = glm::vec3(45.0f * time, 45.0f * time, 45.0f * time);

    glm::mat4 model = temp.getModelMatrix();

    currentShader.setMat4("model", model);
    renderer.renderMeshWithLighting(currentShader, meshManager.get("cubeMesh"), model, lightCube);


    // 2. Use light source shader and render lights

    currentShader = shaderManager.get("lightSourceShader");
    currentShader.use();

    renderer.renderLightSource(currentShader, meshManager.get("cubeMesh"), lightCube);
}
