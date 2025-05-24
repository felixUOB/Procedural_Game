#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaders/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "tools/stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Shader ourShader);

float mixVal = 0.2f;

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
   Shader ourShader("src/shaders/v_shader.glsl", "src/shaders/f_shader.glsl");

   // set vertex data, buffers and configure vertex attributes
   // --------------------------------------------------------
   float vertices[] = {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 2.0f    // top left 
};

   unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
   };  

   unsigned int VBO, VAO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);
   
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // color attribute
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
   glEnableVertexAttribArray(1);

   glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
   glEnableVertexAttribArray(2);
   
   glBindBuffer(VBO, 0);
   glBindBuffer(EBO, 0);
   glBindVertexArray(0);
  
   // load and generate textures
   // --------------------------

   unsigned int texture1, texture2;
   // texture 1
   // ---------
   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1); 
   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   // load image, create texture and generate mipmaps
   int width, height, nrChannels;
   stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
   // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
   unsigned char *data = stbi_load("src/elements/container.jpg", &width, &height, &nrChannels, 0);
   if (data)
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
      std::cout << "Failed to load texture" << std::endl;
   }
   stbi_image_free(data);
   // texture 2
   // ---------
   glGenTextures(1, &texture2);
   glBindTexture(GL_TEXTURE_2D, texture2);
   // set the texture wrapping parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   // set texture filtering parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   // load image, create texture and generate mipmaps
   data = stbi_load("src/elements/waltuh.jpg", &width, &height, &nrChannels, 0);
   if (data)
   {
      // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
      std::cout << "Failed to load texture" << std::endl;
   }
   stbi_image_free(data);

   // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
   // -------------------------------------------------------------------------------------------
   ourShader.use(); // don't forget to activate/use the shader before setting uniforms!
   // either set it manually like so:
   glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
   // or set it via the texture class
   ourShader.setInt("texture2", 1);


   // game loop
   // ---------
   while(!glfwWindowShouldClose(window)) {   
      processInput(window, ourShader);

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      // bind textures on corresponding texture units
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, texture1);
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, texture2);

      ourShader.setFloat("mixVal", mixVal);
      // render container
      ourShader.use();
      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      
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
void processInput(GLFWwindow *window, Shader ourShader) {
   if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
      glfwSetWindowShouldClose(window, true);
   } else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
   mixVal += 0.1f;
   if (mixVal >= 1.0f)
      mixVal = 1.0f;
   } else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
   mixVal -= 0.1f;
   if (mixVal <= 0.0f)
      mixVal = 0.0f;
   }
}