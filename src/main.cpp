#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void render(unsigned int shaderProgram);

int main() {

   // glfw: initialize and configure
   // ------------------------------
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   // glfw window creation
   // --------------------
   GLFWwindow* window = glfwCreateWindow(800, 600, "Engine", NULL, NULL);
   if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

   // glad: load OpenGL function pointers
   // -----------------------------------
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }  

   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   // build and compile shader program
   // ------------------------------------
   Shader ourShader("src/v_shader.glsl", "src/f_shader.glsl");

   // set vertex data, buffers and configure vertex attributes
   // --------------------------------------------------------
   float vertices[] = {
      // positions         // colors
      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
      -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
   };    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
   glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can 
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(VAO);

   // game loop
   // ---------
   while(!glfwWindowShouldClose(window)) {   
      processInput(window);

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);


      // render the triangle
      ourShader.use();
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      
      glfwSwapBuffers(window);
      glfwPollEvents(); 
   }
   
   // deallocate all resources
   // ------------------------
   glDeleteVertexArrays(1, &VAO);
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
void processInput(GLFWwindow *window) {
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
       glfwSetWindowShouldClose(window, true);
}

// render each frame by first clearing, defining the shader program, and drawing the triangles
// -------------------------------------------------------------------------------------------
void render(unsigned int shaderProgram) {
   
}