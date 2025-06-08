#ifndef MESH_H
#define MESH_H

#include <config/glad/glad.h>
#include <config/glm/glm/glm.hpp>
#include <vector>

class Mesh {
    public: 
        Mesh(const std::vector<float>& vertices, bool hasTexture, bool hasNormal);

        void Draw() const;
        void Cleanup();

    private:
        unsigned int VAO, VBO;
        bool hasTexture;
        bool hasNormal;
        std::vector<float> m_vertices;

        void setupMesh();
};

#endif
