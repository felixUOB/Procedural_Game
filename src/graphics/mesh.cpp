#include "graphics/mesh.h"

#include <config/glad/glad.h>
#include <config/glm/glm/glm.hpp>
#include <config/glm/glm/gtc/matrix_transform.hpp>
#include <config/glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <unistd.h>

Mesh::Mesh(const std::vector<float>& vertices, bool hasTexture, bool hasNormal)
    : hasTexture(hasTexture), hasNormal(hasNormal), m_vertices(vertices)
{
    setupMesh();
}

void Mesh::Draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / (3 + (hasTexture ? 2 : 0) + (hasNormal ? 3 : 0)));
    glBindVertexArray(0);
}

void Mesh::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::setupMesh() 
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);

    int stride = 3;
    if (hasTexture) stride += 2;
    if (hasNormal) stride += 3;

    int offset = 0;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    glEnableVertexAttribArray(0);
    offset += 3;

    if (hasTexture) {
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(1);
        offset += 2;
    }

    if (hasNormal) {
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    glBindVertexArray(0);
}