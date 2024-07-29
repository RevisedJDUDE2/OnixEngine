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
    -0.5, -0.5, 0.0, 
     0.5, -0.5, 0.0, 
     0.5,  0.5, 0.0,
    -0.5,  0.5, 0.0
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void**)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  while (!window.ShouldClose()) {
    Onix::ClearColorAndSet(0.0, 0.0, 0.0);
    Program.UseProgram();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  return 0;
}