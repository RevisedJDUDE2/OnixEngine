#include "Onix.hpp"
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"

//# EXTERNALS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main(void) {
  glm::vec2 translations[10];
  translations[0].x = -0.5f;
  translations[0].y = 0.0f;
  Onix::Init_GLFW();
  Onix::Window MainWindow("Onix Sample", 800, 600);
  //Onix::Init_GL(); use this for GLEW
  Onix::Init_GLAD(); //AND THIS FOR GLAD

  Onix::Shader VertexShader("default.vert.glsl", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("default.frag.glsl", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);
  Onix::Buffer Instanced(GL_ARRAY_BUFFER, 10 * sizeof(glm::vec2), &translations[0], GL_STATIC_DRAW);
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

#pragma region BUFFERS

  Onix::Buffer VAO(GL_VERTEX_ARRAY);
  VAO.Bind();
  Onix::Buffer VBO(GL_ARRAY_BUFFER, sizeof(Triangles), Triangles, GL_STATIC_DRAW);
  Onix::Buffer EBO(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
  Onix::SetVertexAttribPointer(0, 3, sizeof(Vertices), (void*)offsetof(Vertices, Position));
  Onix::SetVertexAttribPointer(1, 3, sizeof(Vertices), (void*)offsetof(Vertices, Color));
  Onix::EnableVertexAttrib(VBO, 2);
  Instanced.Bind();
  Onix::SetVertexAttribPointer(VBO, 2, 2, 2 * sizeof(float), (void*)0);
  VBO.Unbind();
  glVertexAttribDivisor(2, 1);

#pragma endregion

  while (!glfwWindowShouldClose(MainWindow.Get())) {
    glClear(GL_COLOR_BUFFER_BIT);
    Program.UseProgram();
    if (glfwGetKey(MainWindow.Get(), GLFW_KEY_D)) {
      translations[0].x -= 0.1f;
    }
    int maxx, maxy;
    glfwGetWindowSize(MainWindow.Get(), &maxx, &maxy);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(80.0f), (float)maxx/(float)maxy, 0.1f, 100.f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    GLuint Projection_Location = glGetUniformLocation(Program.GetHandle(), "proj");
    GLuint View_Location = glGetUniformLocation(Program.GetHandle(), "view");
    glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(View_Location, 1, GL_FALSE, &view[0][0]);

    GLuint loc = glGetUniformLocation(Program.GetHandle(), "INSTANCED[0]");
    glUniform2f(loc, translations[0].x, translations[0].y);
    fprintf(stdout, "translation[0].x = %d\r", translations[0].x);
    VAO.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 10);
    glBindVertexArray(0);
    glfwSwapBuffers(MainWindow.Get());
    glfwPollEvents();
  }
  return 0;
}