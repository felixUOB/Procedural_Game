#include <vendor/glad/glad.h>

#include <GLFW/glfw3.h>
#include <vendor/glm/glm/glm.hpp>
#include <vendor/glm/glm/gtc/matrix_transform.hpp>
#include <vendor/glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "camera/camera.h"
#include "core/map.h"
#include "core/renderer.h"
#include "core/timer.h"
#include "core/window.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "tools/mesh_manager.h"
#include "tools/shader_manager.h"
#include "tools/texture_manager.h"
#include "utils/geometry.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool polyMode = false;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// renderer
Renderer renderer(camera, SCR_WIDTH, SCR_HEIGHT);

// config
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// framerate
Timer timer;

int main() {

  GLFWwindow *window = window::init(SCR_WIDTH, SCR_HEIGHT, "Game");
  window::configure(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);

  // glad: load OpenGL function pointers
  // -----------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
  glEnable(GL_DEPTH_TEST);

  // build and compile shader programs and register to shader manager
  // ----------------------------------------------------------------
  Shader cubeLightingShader("shaders/cubes/v_shader.glsl", 
    "shaders/cubes/f_shader.glsl");
  Shader lightSourceShader("shaders/lightSource/v_lightSource.glsl", 
    "shaders/lightSource/f_lightSource.glsl");

  ShaderManager shaderManager;
  shaderManager.registerShader("cubeLightingShader", cubeLightingShader);
  shaderManager.registerShader("lightSourceShader", lightSourceShader);

  // creates meshes and registers to mesh manager
  // --------------------------------------------
  Mesh cubeMesh(geometry::cubeVertices, true, true);
  Mesh lightSourceMesh(geometry::cubeVertices, true, true);

  MeshManager meshManager;
  meshManager.registerMesh("cubeMesh", cubeMesh);
  meshManager.registerMesh("lightSourceMesh", lightSourceMesh);

  // load/generate/register/bind textures
  // ------------------------------------
  TextureManager TextureManager;
  TextureManager.registerTexture(
      "crate", Texture::LoadTexture("assets/textures/crate.jpg"));
  TextureManager.registerTexture(
      "waltuh", Texture::LoadTexture("assets/textures/waltuh.jpg"));
  TextureManager.registerTexture(
      "wall", Texture::LoadTexture("assets/textures/wall.jpg"));
  TextureManager.registerTexture(
      "floor", Texture::LoadTexture("assets/textures/floor.jpg"));
  TextureManager.registerTexture(
      "ceiling", Texture::LoadTexture("assets/textures/ceiling.jpg"));

  TextureManager.bindTexture("crate");
  TextureManager.bindTexture("waltuh");
  TextureManager.bindTexture("wall");
  TextureManager.bindTexture("floor");
  TextureManager.bindTexture("ceiling");

  // load and generate map
  Map map;
  map.load("assets/maps/test_map.json");

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    timer.update();

    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    map.render(renderer, shaderManager, meshManager);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // deallocate all resources
  // ------------------------
  meshManager.cleanup();

  window::terminate();

  printf("Exiting...\n");
  return 0;
}

// glfw: this is called when the window size changes
// -------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
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

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
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