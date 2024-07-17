#include "Onix.hpp"

const float version = 0.01;

int main() {
  printf("Game Version %.2f\n", version);
  Onix::Init_GLFW();
  Onix::Window window("MARIO JUMP!", 800, 600);
  Onix::Init_GLAD();

  Onix::Shader VertexShader("shader.vert", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("shader.frag", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
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

  Onix::Buffer VertexArray(true); //NOW it just a bool that tells Buffer that its a vao
  Onix::Buffer VertexBuffer(GL_ARRAY_BUFFER, sizeof(RectangleMesh), RectangleMesh, GL_STATIC_DRAW);
  Onix::Buffer ElementArray(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

  //Onix::SetVertexAttribPointer(0, 3, sizeof(Vertices), (void**)offsetof(Vertices, Position));
  //ENGINE NOW BROKEN LETS GOO
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void**)offsetof(Vertices, Position));

  VertexArray.Bind();  //TODO: fix Bind() and Unbind() because there oposite

  while (!window.ShouldClose()) {
    Onix::ClearColorAndSet(0.0, 0.0, 0.0);
    VertexArray.Unbind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  return 0;
}