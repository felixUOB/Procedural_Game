#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = "#version 330 core\n"
   "layout (location = 0) in vec3 aPos;\n"
   "void main()\n"
   "{\n"
   "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
   "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
   "out vec4 FragColor;\n"
   "void main()\n"
   "{\n"
   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
   "}\0";

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

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   // build and compile our shader program
   // ------------------------------------
   // vertex shader
   unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);
   // check for shader compile errors
   int success;
   char infoLog[512];
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
   }
   // fragment shader
   unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);
   // check for shader compile errors
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
   }
   // link shaders
   unsigned int shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);
   // check for linking errors
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
   }
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);

   // set vertex data, buffers and configure vertex attributes
   // --------------------------------------------------------
   float vertices[] = {
      0.5f,  0.5f, 0.0f,  // top right
      0.5f, -0.5f, 0.0f,  // bottom right
     -0.5f, -0.5f, 0.0f,  // bottom left
     -0.5f,  0.5f, 0.0f   // top left 
   };
   unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,  // first Triangle
      1, 2, 3   // second Triangle
   };
   unsigned int VBO, VAO, EBO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   glGenBuffers(1, &EBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO); // VAOs store all subsequent VBO calls so we dont need to keep binding the VBOs

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // EBOs allow us to reuse vertex data
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // tell OpenGL how to interperate vertex data
   glEnableVertexAttribArray(0); // enable the vertex attribute 0 (position) in the shader

   glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind the VBO so we can bind other VBOs without affecting this one
   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   glBindVertexArray(0); 
   // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   // game loop
   // ---------
   while(!glfwWindowShouldClose(window)) {   
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindVertexArray(VAO); // bind the VAO (contains VBO and EBO already) to draw the triangles
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
      
      glfwSwapBuffers(window);
      glfwPollEvents(); 
   }
   
   // deallocate all resources
   // ------------------------
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteProgram(shaderProgram);

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