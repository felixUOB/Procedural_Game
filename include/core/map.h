#ifndef MAP_H
#define MAP_H

#include "core/renderer.h"
#include "lighting/light.h"
#include "tools/mesh_manager.h"
#include "tools/shader_manager.h"
#include "utils/gameobj.h"

class Map {
public:
  void load(const std::string &path);
  void render(Renderer &renderer, ShaderManager &shaderManager,
              MeshManager &meshManager);

private:
  std::vector<GameObject> objects;
  std::vector<Light> lights;
};

#endif