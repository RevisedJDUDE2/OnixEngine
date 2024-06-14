#include "Onix.hpp"
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"

//# EXTERNALS
#include <glm/glm.hpp>

int main(void) {
  Onix::Init_GLFW();
  Onix::Window MainWindow("Onix Sample", 800, 600);
  //Onix::Init_GL();
  Onix::Init_GLAD();

  Onix::Shader VertexShader("default.vert.glsl", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("default.frag.glsl", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);

  Vertices Triangles[4] = {
    { { -0.5, -0.5, 0.0 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5, -0.5, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },
    { { -0.5,  0.5, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } }
  };
  unsigned int Indices[6] = {
    0, 1, 2,
    0, 3, 2
  };
  int count = 10;
  glm::vec3* Positions = new glm::vec3[count];
  for (int i = 0; i < count; i++) {
    float ft = 0.1f;
    Positions[i].x = ft;
    Positions[i].y = ft;
    ft += 0.1f;
  };
  //Onix::Buffer VAO(GL_VERTEX_ARRAY);
  //VAO.Bind();
  //Onix::Buffer VBO(GL_ARRAY_BUFFER, sizeof(Triangles), Triangles, GL_STATIC_DRAW);
  //Onix::SetVertexAttribPointer(0, 3, sizeof(Vertices), (void*)offsetof(Vertices, Position));
  //Onix::SetVertexAttribPointer(1, 3, sizeof(Vertices), (void*)offsetof(Vertices, Color));
  //Onix::Buffer EBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
  //unsigned int INSTANCEDVBO;
  //glGenBuffers(1, &INSTANCEDVBO);
  //glBindBuffer(GL_ARRAY_BUFFER, INSTANCEDVBO);
  //glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec3), &Positions[0], GL_STATIC_DRAW);
  //Onix::SetVertexAttribPointer(2, 3, sizeof(glm::vec3), (void*)0);
  //glVertexAttribDivisor(2, 1);
  //VAO.Unbind();
  GLuint VAO, VBO, EBO, INSTANCED;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Triangles), Triangles, GL_STATIC_DRAW);

  glGenBuffers(1, &INSTANCED);
  glBindBuffer(GL_ARRAY_BUFFER, INSTANCED);
  glBufferData(GL_ARRAY_BUFFER, count * 3 * sizeof(float), &Positions[0], GL_STATIC_DRAW);

  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)offsetof(Vertices, Position));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*)offsetof(Vertices, Color));
  glBindBuffer(GL_ARRAY_BUFFER, INSTANCED);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
  glVertexAttribDivisor(2, 1);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(MainWindow.Get())) {
    glClear(GL_COLOR_BUFFER_BIT);
    if (glfwGetKey(MainWindow.Get(), GLFW_KEY_W)) {
      Positions[0].x += 0.1f;
    }
    Program.UseProgram();
    glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 10);
    glfwSwapBuffers(MainWindow.Get());
    glfwPollEvents();
  }
  //delete[] Positions;
  return 0;
}