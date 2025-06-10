#include "tools/mesh_manager.h"
#include "graphics/mesh.h"
#include <iostream>

void MeshManager::registerMesh(const char *name, Mesh &mesh) {
  std::cout << "Registering mesh: " << name << std::endl;
  meshes.insert({name, mesh});
}

Mesh &MeshManager::get(const char *name) { return meshes.at(name); }

void MeshManager::cleanup() {
  for (auto &pair : meshes) {
    std::cout << "Cleaning: " << pair.first << std::endl;
    pair.second.cleanup();
  }
}