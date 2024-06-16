#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Onix.hpp"
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"

//# EXTERNALS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main(void) {
  Onix::Init_GLFW();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  Onix::Window MainWindow("Onix Sample", 800, 600);
  //Onix::Init_GL(); use this for GLEW
  Onix::Init_GLAD(); //AND THIS FOR GLAD

  Onix::Shader VertexShader("default.vert.glsl", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader("default.frag.glsl", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);
  //Onix::Buffer Instanced(GL_ARRAY_BUFFER, 10 * sizeof(glm::vec2), &translations[0], GL_STATIC_DRAW);//2vec
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(MainWindow.Get(), true);
  ImGui_ImplOpenGL3_Init("#version 330 core");
  //glm::mat4 *MODEL_MATRICES = new glm::mat4[10];
  std::unique_ptr<glm::mat4[]> MODEL_MATRICES(new glm::mat4[10]);
  for(unsigned int i = 0; i < 10; i++) {
    MODEL_MATRICES[i] = glm::mat4(1.0f);
  }
  MODEL_MATRICES[0] = glm::translate(MODEL_MATRICES[0], glm::vec3(-1.0f, -1.0f, 0.0));
  MODEL_MATRICES[1] = glm::translate(MODEL_MATRICES[0], glm::vec3(-1.5f, -1.5f, 0.0));
  Onix::Buffer Instanced(GL_ARRAY_BUFFER, 10 * sizeof(glm::mat4), &MODEL_MATRICES[0], GL_STATIC_DRAW);//2vec

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
  Instanced.Bind();
  GLsizei vec4Size = sizeof(glm::vec4);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, reinterpret_cast<void*>(1 * vec4Size));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, reinterpret_cast<void*>(2 * vec4Size));

  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, reinterpret_cast<void*>(3 * vec4Size));

  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  VBO.Unbind();
  //glVertexAttribDivisor(2, 1);
  //glVertexAttribDivisor(3, 1);
  //glVertexAttribDivisor(4, 1);
  //glVertexAttribDivisor(5, 1);

#pragma endregion
  float x = 0.0f;
  float last;
  bool demo = true;
  while (!glfwWindowShouldClose(MainWindow.Get())) {
    glClear(GL_COLOR_BUFFER_BIT);
    Program.UseProgram();
    float curr = (float)glfwGetTime(), delta = curr - last;
    last = curr;
    if (glfwGetKey(MainWindow.Get(), GLFW_KEY_D) == GLFW_PRESS) {
      x += 1.0f * delta;
    }
    int maxx, maxy;
    glfwGetFramebufferSize(MainWindow.Get(), &maxx, &maxy);


    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(80.0f), (float)maxx/(float)maxy, 0.1f, 100.f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    GLuint Projection_Location = glGetUniformLocation(Program.GetHandle(), "proj");
    GLuint View_Location = glGetUniformLocation(Program.GetHandle(), "view");
    glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(View_Location, 1, GL_FALSE, &view[0][0]);

    MODEL_MATRICES[0] = glm::translate(MODEL_MATRICES[0], glm::vec3(x, 0.0f, 0.0f));

    VAO.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 10);
    glBindVertexArray(0);
    glfwSwapBuffers(MainWindow.Get());
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if(demo)
      ImGui::ShowDemoWindow(&demo);
    {
      ImGui::Begin("Hello");
      ImGui::Text("Hello From Onix");
      ImGui::End();
    }
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  return 0;
}