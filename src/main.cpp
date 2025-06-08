#include <config/glad/glad.h>
#include <GLFW/glfw3.h>

#include <config/glm/glm/glm.hpp>
#include <config/glm/glm/gtc/matrix_transform.hpp>
#include <config/glm/glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "graphics/shader.h"
#include "camera/camera.h"
#include "graphics/texture.h"
#include "lighting/light.h"

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

// config
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//framerate
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

// lighting
Light lightCube{
    Light::Type::Point,
    glm::vec3(1.2f, 2.0f, 2.0f),
    glm::vec3(1.0f, 1.0f, 1.0f) // Sunset RGB
};

int main() {

   // glfw: initialize
   // ------------------------------
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   // glfw window creation
   // --------------------
   // GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Engine", glfwGetPrimaryMonitor(), NULL);
   GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game", NULL, NULL);
   if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
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

   // set vertex data, buffers and configure vertex attributes
   // --------------------------------------------------------
   float vertices[] = {
    // Position            // Texture Coords       // Normals
    -0.5f, -0.5f, -0.5f,      0.0f, 0.0f,       0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,      1.0f, 0.0f,       0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,      1.0f, 1.0f,       0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,      1.0f, 1.0f,       0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,      0.0f, 1.0f,       0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,      0.0f, 0.0f,       0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,      0.0f, 0.0f,       0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,      1.0f, 0.0f,       0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,      1.0f, 1.0f,       0.0f,  0.0f,  1.0f,
     0.5f,  0.5f,  0.5f,      1.0f, 1.0f,       0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,      0.0f, 1.0f,       0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,      0.0f, 0.0f,       0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f,  0.5f,      1.0f, 0.0f,      -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,      1.0f, 1.0f,      -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,      0.0f, 1.0f,      -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,      0.0f, 1.0f,      -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,      0.0f, 0.0f,      -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,      1.0f, 0.0f,      -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,      1.0f, 0.0f,       1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,      1.0f, 1.0f,       1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,      0.0f, 1.0f,       1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,      0.0f, 1.0f,       1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,      0.0f, 0.0f,       1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,      1.0f, 0.0f,       1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,      0.0f, 1.0f,       0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,      1.0f, 1.0f,       0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,      1.0f, 0.0f,       0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,      1.0f, 0.0f,       0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,      0.0f, 0.0f,       0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,      0.0f, 1.0f,       0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,      0.0f, 1.0f,       0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,      1.0f, 1.0f,       0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,      1.0f, 0.0f,       0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,      1.0f, 0.0f,       0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,      0.0f, 0.0f,       0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,      0.0f, 1.0f,       0.0f,  1.0f,  0.0f
};

   unsigned int VBO, cubeVAO;
   glGenVertexArrays(1, &cubeVAO);
   glGenBuffers(1, &VBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(cubeVAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // texture coord attribute
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
   glEnableVertexAttribArray(1);

   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
   glEnableVertexAttribArray(2);

   glBindVertexArray(0); // Unbind VAO to reduce chance of accidental changes
   
   unsigned int lightVAO;
   glGenVertexArrays(1, &lightVAO);
   glBindVertexArray(lightVAO);
   // we only need to bind to the VBO, the container's VBO's data already contains the data.
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   // set the vertex attribute (only position, we dont care about texture but as we are using same VBO we need to have correct stride length)
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   // load and generate textures using custom Loader
   // ----------------------------------------------

   unsigned int texture1 = Texture::LoadTexture("assets/textures/container.jpg");
   unsigned int texture2 = Texture::LoadTexture("assets/textures/waltuh.jpg");

   // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
   // -------------------------------------------------------------------------------------------
   cubeLightingShader.use();
   cubeLightingShader.setInt("texture1", 0);
   cubeLightingShader.setInt("texture2", 1);
   cubeLightingShader.setVec3("object_color", 1.0f, 1.0f, 1.0f);

   lightCube.initToShader(cubeLightingShader, "lightSource");

   // render loop
   // -----------
   while (!glfwWindowShouldClose(window))
   {
      float currentFrame = (float)glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      // input
      // -----
      processInput(window);

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // bind textures on corresponding texture units
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);

      // activate shader
      cubeLightingShader.use();

      // pass projection matrix to shader (note that in this case it could change every frame)
      glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
      cubeLightingShader.setMat4("projection", projection);

      // camera/view transformation
      glm::mat4 view = camera.GetViewMatrix();
      cubeLightingShader.setMat4("view", view);

      // world transformation
      glm::mat4 model = glm::mat4(1.0f);
      // model = glm::translate(model, glm::vec3(5.0f, 1.5f, 2.0f));
      model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
      model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
      cubeLightingShader.setMat4("model", model);

      // Matrix that converts normalls to worldspace - ignores non uniform scaling to ensure normal vec still applies
      cubeLightingShader.setMat3("normalMat", glm::mat3(transpose(inverse(model))));


      cubeLightingShader.setVec3("lightSource_position", lightCube.getPosition());  


      // render boxes
      glBindVertexArray(cubeVAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);
      glBindVertexArray(0);

      // render lightSource
      lightSourceShader.use();
      lightSourceShader.setMat4("projection", projection);
      lightSourceShader.setMat4("view", view);
      model = glm::mat4(1.0f);
      model = glm::translate(model, lightCube.getPosition());
      model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
      lightSourceShader.setMat4("model", model);

      glBindVertexArray(lightVAO);
      glDrawArrays(GL_TRIANGLES, 0, 36);

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // deallocate all resources
   // ------------------------
   glDeleteVertexArrays(1, &cubeVAO);
   glDeleteBuffers(1, &VBO);

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
      camera.ProcessKeyboard(FORWARD, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      camera.ProcessKeyboard(BACKWARD, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
      camera.ProcessKeyboard(LEFT, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
      camera.ProcessKeyboard(RIGHT, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
      camera.ProcessKeyboard(UP, deltaTime);
   if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
      camera.ProcessKeyboard(DOWN, deltaTime);
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