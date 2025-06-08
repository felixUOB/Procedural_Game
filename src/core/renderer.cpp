#include "core/renderer.h"
#include "camera/camera.h"

#include <config/glad/glad.h>
#include <config/glm/glm/glm.hpp>
#include <config/glm/glm/gtc/matrix_transform.hpp>
#include <config/glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <unistd.h>

Renderer::Renderer(Camera& camera, int screenWidth, int screenHeight) 
    : camera(camera), screenWidth(screenWidth), screenHeight(screenHeight) {}

void Renderer::renderMeshWithLighting(Shader& shader, Mesh& mesh, const glm::mat4& model, const Light& light)
{
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();

    shader.setMat4("projection", projection);
    shader.setMat4("view", view);
    shader.setMat4("model", model);

    glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(model)));
    shader.setMat3("normalMat", normalMat);

    shader.setVec3("lightSource_position", light.getPosition());

    mesh.Draw();
}
