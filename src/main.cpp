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


float vertices[] = {
   -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};  

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void render() {
   glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   unsigned int VBO;
   glGenBuffers(1, &VBO);  // Generate a buffer object

   glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the buffer object to the GL_ARRAY_BUFFER target

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Copy vertex data to the binded buffer
}

int main() {
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

   GLFWwindow* window = glfwCreateWindow(800, 600, "Engine", NULL, NULL);
   if (window == NULL) {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return -1;
   }
   
   glfwMakeContextCurrent(window);

   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cout << "Failed to initialize GLAD" << std::endl;
      return -1;
   }  

   glViewport(0, 0, 800, 600);

   // SHADERS

   unsigned int vertexShader;
   vertexShader = glCreateShader(GL_VERTEX_SHADER);

   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   unsigned int fragmentShader;
   fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);

   int vertSuccess;
   int fragSuccess;
   char infoLog[512];
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertSuccess);
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragSuccess);

   if(!vertSuccess || !fragSuccess) {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      if (!vertSuccess)
         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      if (!fragSuccess)
         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

      glfwTerminate();
      return -1;
   } else {
      std::cout << "Shaders compiled successfully!" << std::endl;
   }

   unsigned int shaderProgram;
   shaderProgram = glCreateProgram();

   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   int linkSuccess;
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkSuccess);
   if(!linkSuccess) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      glfwTerminate();
      return -1;
   } else {
      std::cout << "Shaders linked successfully!" << std::endl;
      glUseProgram(shaderProgram);
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);  
   }


   // GAME LOOP

   while(!glfwWindowShouldClose(window)) {   
      processInput(window);

      render();
      
      glfwPollEvents();    
      glfwSwapBuffers(window);
   }

   glfwTerminate();
   
   printf("Exiting...\n");
   return 0;
}