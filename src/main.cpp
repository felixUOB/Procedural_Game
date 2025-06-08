#include <config/glad/glad.h>
#include <GLFW/glfw3.h>

#include <config/glm/glm/glm.hpp>
#include <config/glm/glm/gtc/matrix_transform.hpp>
#include <config/glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "graphics/shader.h"
#include "camera/camera.h"
#include "graphics/texture.h"
#include "lighting/light.h"
#include "graphics/mesh.h"
#include "core/renderer.h"
#include "core/geometry.h"
#include "core/timer.h"
#include "core/window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool polyMode = false;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// renderer
Renderer renderer(camera, SCR_WIDTH, SCR_HEIGHT);  // lowercase camera and ints, actual objects/values

// config
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//framerate
Timer timer;

// lighting
Light lightCube{
    glm::vec3(1.2f, 2.0f, 2.0f),
    glm::vec3(1.0f, 1.0f, 1.0f)
};

int main() {

   GLFWwindow* window = window::init(SCR_WIDTH, SCR_HEIGHT, "Game");

   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetCursorPosCallback(window, mouse_callback);


   
   // glad: load OpenGL function pointers
   // -----------------------------------
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }  

   // build and compile shader program
   // ------------------------------------
   Shader cubeLightingShader("shaders/cubes/v_shader.glsl", "shaders/cubes/f_shader.glsl");
   Shader lightSourceShader("shaders/lightSource/v_lightSource.glsl", "shaders/lightSource/f_lightSource.glsl");

   // glfw: config
   // ------------
   glEnable(GL_DEPTH_TEST);
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   // creates meshes
   // --------------------------------------------------------

   Mesh cubeMesh(geometry::cubeVertices, true, true);
   Mesh lightSourceMesh(geometry::cubeVertices, true, true);

   // load and generate textures
   // --------------------------

   unsigned int texture1 = Texture::LoadTexture("assets/textures/container.jpg");
   unsigned int texture2 = Texture::LoadTexture("assets/textures/waltuh.jpg");

   // bind textures on corresponding texture units - pre program run
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texture1);
   glActiveTexture(GL_TEXTURE1);
   glBindTexture(GL_TEXTURE_2D, texture2);

   // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
   // -------------------------------------------------------------------------------------------

   cubeLightingShader.use();
   cubeLightingShader.informTextureBindings(2);
   cubeLightingShader.setVec3("object_color", 1.0f, 1.0f, 1.0f);

   lightCube.initToShader(cubeLightingShader, "lightSource");

   // render loop
   // -----------
   while (!glfwWindowShouldClose(window))
   {
      timer.update();

      // input
      // -----
      processInput(window);

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // world transformation
      glm::mat4 model = glm::mat4(1.0f);
      // model = glm::translate(model, glm::vec3(5.0f, 1.5f, 2.0f));
      model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
      model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
      cubeLightingShader.setMat4("model", model);

      renderer.renderMeshWithLighting(cubeLightingShader, cubeMesh, model, lightCube);
      renderer.renderLightSource(lightSourceShader, cubeMesh, lightCube);

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // deallocate all resources
   // ------------------------
   cubeMesh.Cleanup();
   lightSourceMesh.Cleanup();

   glfwTerminate();
   
   printf("Exiting...\n");
   return 0;
}

// glfw: this is called when the window size changes
// -------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
   glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
   static bool pKeyWasPressed = false;
   static bool polyMode = false;

   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

   if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      camera.ProcessKeyboard(FORWARD, timer.deltaTime);
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      camera.ProcessKeyboard(BACKWARD, timer.deltaTime);
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera.ProcessKeyboard(LEFT, timer.deltaTime);
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera.ProcessKeyboard(RIGHT, timer.deltaTime);
   if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      camera.ProcessKeyboard(UP, timer.deltaTime);
   if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
      camera.ProcessKeyboard(DOWN, timer.deltaTime);
   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
      lightCube.changeXPos(0.01);
   if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
      lightCube.changeXPos(-0.01);
   if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
      lightCube.changeZPos(-0.01);
   if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
      lightCube.changeZPos(0.01);

   bool pKeyIsPressed = glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS;
   if (pKeyIsPressed && !pKeyWasPressed) {
      polyMode = !polyMode;
      if (polyMode)
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
         glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   }
   pKeyWasPressed = pKeyIsPressed;
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}