#ifndef RENDERER_H
#define RENDERER_H

#include "camera/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "lighting/light.h"
#include <config/glad/glad.h>
#include <string>
#include <config/glm/glm/glm.hpp>


class Renderer
{
    public:
        Renderer(Camera& camera, int screenWidth, int screenHeight);

        void renderMeshWithLighting(Shader& shader, Mesh& mesh, const glm::mat4& model, const Light& light);
        void renderLightSource(Shader& shader, Mesh& mesh, const Light& light);


    private:
        Camera& camera;
        int screenWidth, screenHeight;
};

#endif