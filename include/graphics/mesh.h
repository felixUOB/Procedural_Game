#ifndef MESH_H
#define MESH_H

#include <vector>

class Mesh {
public:
  Mesh(const std::vector<float> &vertices, bool hasTexture, bool hasNormal);

  void draw() const;
  void cleanup();

private:
  unsigned int VAO, VBO;
  bool hasTexture;
  bool hasNormal;
  std::vector<float> m_vertices;

  void setupMesh();
};

#endif
