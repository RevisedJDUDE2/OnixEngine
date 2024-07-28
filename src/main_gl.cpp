#include "Onix.hpp"

const float version = 0.01;

int main() {
  printf("Game Version %.2f\n", version);
  Onix::Init_GLFW();
  Onix::Window window("Game", 800, 600);
  Onix::Init_GLAD();

  Onix::Shader VertexShader("shader.vert", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("shader.frag", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  //GL_TYPE_EX_SHADER_PROGRAM is my own #define not opengls
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);

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

  Onix::Buffer VertexArray(true, 0);
  Onix::Buffer VertexBuffer(false, GL_ARRAY_BUFFER);
  Onix::Buffer ElementArray(false, GL_ELEMENT_ARRAY_BUFFER);
  VertexArray.GenBuffers();
  VertexArray.Bind();
  Onix::CheckGLError("Vao Bind");

  VertexBuffer.Bind();
  Onix::CheckGLError("Vbo Bind");
  VertexBuffer.SetData(sizeof(RectangleMesh), RectangleMesh, GL_STATIC_DRAW);
  Onix::CheckGLError("Vbo Set Data");

  ElementArray.Bind();
  Onix::CheckGLError("Ebo Bind");
  ElementArray.SetData(sizeof(Indices), Indices, GL_STATIC_DRAW);
  Onix::CheckGLError("Ebo Set Data");

  Onix::SetVertexAttribPointer(false, 0, 3, sizeof(Vertices), (void**)offsetof(Vertices, Position));
  Onix::CheckGLError("SetVertexAttribPointer");

  VertexBuffer.Unbind();
  ElementArray.Unbind();
  VertexArray.Unbind();

  while (!window.ShouldClose()) {
    Onix::ClearColorAndSet(0.0, 0.0, 0.0);
    Program.UseProgram();
    Onix::CheckGLError("Use Program");
    VertexArray.Bind();
    Onix::CheckGLError("Vao Bind Before Draw");
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    Onix::CheckGLError("Draw Elements");

    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  return 0;
}