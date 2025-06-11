#include "core/map.h"
#include "core/renderer.h"
#include "graphics/shader.h"
#include "tools/mesh_manager.h"
#include "tools/shader_manager.h"
#include "utils/gameobj.h"
#include "utils/json_converter.h"

#include <fstream>
#include <iostream>
#include <vendor/json.hpp>

void Map::load(const std::string &path) {
  std::cout << "Loading Map from: " << path << std::endl;
  nlohmann::json mapData;

  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Could not open JSON file!" << std::endl;
    return;
  }

  file >> mapData;

  for (auto &object : mapData) {

    glm::vec3 t_position = JsonConverter::jsonVecToVec3(object["position"]);
    glm::vec3 t_rotation = JsonConverter::jsonVecToVec3(object["rotation"]);
    glm::vec3 t_scale = JsonConverter::jsonVecToVec3(object["scale"]);

    Transform transform;
    transform.position = t_position;
    transform.rotation = t_rotation;
    transform.scale = t_scale;

    std::string objType = object["type"];
    if (objType == "crate") {
      cubeObjects.push_back({CRATE, transform});

    } else if (objType == "wall") {
      cubeObjects.push_back({WALL, transform});

   } else if (objType == "waltuh") {
      cubeObjects.push_back({WALTUH, transform});

    } else if (objType == "lightSource") {
      glm::vec3 color = JsonConverter::jsonVecToVec3(object["color"]);

      // Create a light from this object
      Light light(transform.position, color);
      lights.push_back(light);
    } else {
      std::cerr << "ERROR - LOAD: INVALID OBJECT TYPE" << std::endl;
    }
  }
}

void Map::render(Renderer &renderer, ShaderManager &shaderManager,
                 MeshManager &meshManager) {
  // Retreiving Meshes
  Mesh &cubeMesh = meshManager.get("cubeMesh");

  // Retrieving Shaders
  Shader &cubeShader = shaderManager.get("cubeLightingShader");
  Shader &lightSourceShader = shaderManager.get("lightSourceShader");

  for (size_t i = 0; i < lights.size(); ++i) {
    lights[i].initToShader(cubeShader, "lights[" + std::to_string(i) + "]");
  }

  // Render all lights
  lightSourceShader.use();
  for (auto &light : lights) {
    renderer.renderLightSource(lightSourceShader, cubeMesh, light);
  }

  cubeShader.use();
  cubeShader.setInt("numLights", lights.size());

  for (auto &item : cubeObjects) {
    Transform temp = item.transform;
    glm::mat4 model = temp.getModelMatrix();

    if (item.type == CRATE) {
      cubeShader.setInt("activeTexture", 0);
    } else if (item.type == WALTUH) {
      cubeShader.setInt("activeTexture", 1);
    } else if (item.type == WALL) {
      cubeShader.setInt("activeTexture", 2);
   
    } else {
      std::cout << "ERROR - RENDER: INVALID OBJECT TYPE" << std::endl;
    }

    cubeShader.setMat4("model", model);
    renderer.renderMeshWithLighting(cubeShader, cubeMesh, model);
  }
}
