#include <iostream>
#include "Onix.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main() {
  Onix::Init_GLFW();
  Onix::Window window("Horror Game", 800, 600);
  Onix::Init_GLAD();

  Onix::Shader VertexShader("main.vert", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("main.frag", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);
  
  Vertices CUBE[24] = {
    { { -0.5, -0.5, 0.5 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5, -0.5, 0.5 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, 0.5 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, 0.5 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },   //FIRST FACE
    { { -0.5,  0.5, 0.5 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },
    { { -0.5, -0.5, 0.5 }, { 1.0, 0.0, 0.0 }, { 0.0, 0.0 } },

    { {  0.5, -0.5,  0.5 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5, -0.5, -0.5 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { { -0.5, -0.5,  0.5 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { { -0.5, -0.5,  0.5 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },  //FIRST BOTTOM
    { { -0.5, -0.5, -0.5 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5, -0.5, -0.5 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0 } },

    { {  0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },
    { { -0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, -0.5 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, -0.5 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },  // SECOND FACE (BACK)
    { { -0.5,  0.5, -0.5 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },
    { { -0.5, -0.5, -0.5 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0 } },

    { { -0.5,  0.5,  0.5 }, { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5,  0.5 }, { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, -0.5 }, { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { {  0.5,  0.5, -0.5 }, { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } },  //SECOND BOTTOM (TOP)
    { { -0.5,  0.5, -0.5 }, { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } },
    { { -0.5,  0.5, 0.5 },  { 1.0, 1.0, 0.0 }, { 0.0, 0.0 } },
  };

  Onix::Buffer VAO(GL_VERTEX_ARRAY);
  Onix::Buffer VBO(GL_ARRAY_BUFFER, sizeof(CUBE), CUBE, GL_STATIC_DRAW);

  Onix::SetVertexAttribPointer(0, 3, sizeof(Vertices), (void**)offsetof(Vertices, Position));
  Onix::SetVertexAttribPointer(1, 3, sizeof(Vertices), (void**)offsetof(Vertices, Color));
  //VAO.Unbind();

  glViewport(0, 0, 800, 600);

  glEnable(GL_DEPTH_TEST);
  bool condition = false;
  float cooldown = 0.5;
  float last;
  while (!window.ShouldClose()) {
    float time_attr = (float)glfwGetTime();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    int maxx, maxy;
    glfwGetWindowSize(window.Get(), &maxx, &maxy);
    glViewport(0, 0, maxx, maxy);

    float current = (float)glfwGetTime();
    if (window.isKeyPressed(GLFW_KEY_F11) && (current - last > cooldown)) {
      condition = !condition;
      window.SetFullscreen(condition);
      last = current;
    }
    if (window.isKeyPressed(GLFW_KEY_ESCAPE)) {
      glfwTerminate();
      break;
    }

    //DEFINE
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, time_attr, glm::vec3(0.0, 1.0f, 0.0));

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)maxx / (float)maxy, 0.1f, 100.0f);

    Program.UseProgram();
    
    //SET
    unsigned int Location_OF_model = glGetUniformLocation(Program.GetHandle(), "model");
    glUniformMatrix4fv(Location_OF_model, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int Location_OF_view = glGetUniformLocation(Program.GetHandle(), "view");
    glUniformMatrix4fv(Location_OF_view, 1, GL_FALSE, &view[0][0]);

    unsigned int Location_OF_proj = glGetUniformLocation(Program.GetHandle(), "proj");
    glUniformMatrix4fv(Location_OF_proj, 1, GL_FALSE, &projection[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, 24);
    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  
  return 0;
}