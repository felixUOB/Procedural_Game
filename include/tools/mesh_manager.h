#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include "graphics/mesh.h"
#include <unordered_map>

class MeshManager {
public:
  void registerMesh(const char *name, Mesh &mesh);
  Mesh &get(const char *name);
  void cleanup();

private:
  std::unordered_map<std::string, Mesh> meshes;
};

#endif