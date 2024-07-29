#include "Onix.hpp"

const float version = 1.7;

int main() {
  printf("Game Version %.1f\n", version);
  Onix::Init_GLFW();
  Onix::Window window("Game", 800, 600);
  Onix::Init_GLAD();

  Onix::Shader VertexShader("shader.vert", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("shader.frag", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  //GL_TYPE_EX_SHADER_PROGRAM is my own #define not opengls
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);
  Program.CheckError();

  Vertices RectangleMesh[4] = {
    { { -0.5, -0.5, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5, -0.5, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { { -0.5,  0.5, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0 } }
  };

  unsigned int Indices[] = {
      0, 1, 2,
      2, 3, 0
  };
  
  Onix::VertexArray VAO;
  Onix::Buffer VBO(GL_ARRAY_BUFFER, sizeof(RectangleMesh), RectangleMesh, GL_STATIC_DRAW);
  Onix::Buffer EBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
  Onix::EnableVertexAttrib(0);
  Onix::SetVertexAttribPointer(true, 0, 3, sizeof(Vertices), (void**)offsetof(Vertices, Position));
  Onix::CheckGLError("Onix::SetVertexAttribPointer");
  EBO.Unbind();
  VBO.Unbind();
  VAO.Unbind();

  while (!window.ShouldClose()) {
    Onix::ClearColorAndSet(0.0, 0.0, 0.0);
    Program.UseProgram();
    VAO.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  return 0;
}