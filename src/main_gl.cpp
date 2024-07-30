#include "Onix.hpp"

const float version = 1.7;

int main() {
  printf("Game Version %.1f\n", version);
  Onix::Init_GLFW();
  Onix::Window window("Game", 800, 600);
  Onix::Init_GLAD();

  Onix::Shader VertexShader("./resources/shader.vert", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("./resources/shader.frag", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  //GL_TYPE_EX_SHADER_PROGRAM is my own #define not opengls
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);
  Program.CheckError();

  float RectangleMesh[] = {
    -0.5, -0.5, 0.0, 0.0,  
     0.5, -0.5, 1.0, 0.0,
     0.5,  0.5, 1.0, 1.0,
    -0.5,  0.5, 0.0, 1.0
  };

  unsigned int Indices[6] = {
      0, 1, 2,
      2, 3, 0
  };
  
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(RectangleMesh), RectangleMesh, GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void**)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void**)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);

  int imageWidth, imageHeight, imageChannels;
  unsigned char* imageHandle = stbi_load("./resources/dirt.jpg", &imageWidth, &imageHeight, &imageChannels, 0);

  unsigned int textureHandle;
  glGenTextures(1, &textureHandle);
  glBindTexture(GL_TEXTURE_2D, textureHandle);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageHandle);
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  
  while (!window.ShouldClose()) {
    Onix::ClearColorAndSet(0.0, 0.0, 0.0);
    Program.UseProgram();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureHandle);
    
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0f));
    proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f);
    unsigned int viewloc = glGetUniformLocation(Program.GetHandle(), "view");
    unsigned int projloc = glGetUniformLocation(Program.GetHandle(), "proj");
    glUniformMatrix4fv(viewloc, 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(projloc, 1, GL_FALSE, &proj[0][0]);

    Onix::SwapBuffersAndPollEvents(243);
    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  return 0;
}