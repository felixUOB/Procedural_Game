#include "core/map.h"
#include "core/renderer.h"
#include "graphics/shader.h"
#include "tools/shader_manager.h"
#include "tools/mesh_manager.h"
#include "utils/gameobj.h"

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
    std::cout << "Loading Map from: " <<  path << std::endl;
    nlohmann::json mapData;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Could not open JSON file!" << std::endl;
        return;
    }

    file >> mapData;

    for (auto& object : mapData) {

        glm::vec3 t_position;
        t_position.x = object["position"][0];
        t_position.y = object["position"][1];
        t_position.z = object["position"][2];

        glm::vec3 t_rotation;
        t_rotation.x = object["rotation"][0];
        t_rotation.y = object["rotation"][1];
        t_rotation.z = object["rotation"][2];

        glm::vec3 t_scale;
        t_scale.x = object["scale"][0];
        t_scale.y = object["scale"][1];
        t_scale.z = object["scale"][2];

        Transform transform;
        transform.position = t_position;
        transform.rotation = t_rotation;
        transform.scale = t_scale;

        Type type;
        GameObject gameObject;

        if (object["type"] == "crate"){
            type = CRATE;
        } else if (object["type"] == "lightSource"){
            type = LIGHT;
        } else {
            type = T_NULL;
        }

        gameObject.type = type;
        gameObject.transform = transform;

        objects.push_back(gameObject);
    }

}

void Map::render(Renderer& renderer, ShaderManager& shaderManager, MeshManager& meshManager, Light& lightCube)
{
    // Retreiving Meshes
    Mesh& cubeMesh = meshManager.get("cubeMesh");

    // Retrieving Shaders
    Shader& cubeShader = shaderManager.get("cubeLightingShader");
    Shader& lightSourceShader = shaderManager.get("lightSourceShader");
    
    // Render all objects
    for (auto& item : objects) {
        if (item.type == CRATE) {
            cubeShader.use();

            Transform temp = item.transform;
            glm::mat4 model = temp.getModelMatrix();

            cubeShader.setMat4("model", model);
            renderer.renderMeshWithLighting(cubeShader, cubeMesh, model, lightCube);
        } else if (item.type == LIGHT){ // THIS NEEDS TO BE FIXED AS CURRENTLY POSITION IS NOT TAKEN FROM MAP

            lightSourceShader.use();
            renderer.renderLightSource(lightSourceShader, cubeMesh, lightCube);
        }
    }
}
