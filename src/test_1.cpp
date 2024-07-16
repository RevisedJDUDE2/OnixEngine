#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Onix.hpp"
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Onix_Physics.hpp"
#include "Texture.hpp"

//# EXTERNALS
#include <glm/glm.hpp>
#include <glm/ext.hpp>

int test_program_1(int argc, const char** argv) {
  fprintf(stdout, "-> %d;\n", argc);
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
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  ImGui::StyleColorsLight();
  ImGui_ImplGlfw_InitForOpenGL(MainWindow.Get(), true);
  ImGui_ImplOpenGL3_Init("#version 330 core");
  //glm::mat4 *MODEL_MATRICES = new glm::mat4[10];
  std::unique_ptr<glm::mat4[]> MODEL_MATRICES(new glm::mat4[10]);
  for(int i = 0; i < 10; i++) {
    MODEL_MATRICES[i] = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Place all instances at origin
  }
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
  std::size_t vec4Size = sizeof(glm::vec4);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));

  glEnableVertexAttribArray(5);
  glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);
  glVertexAttribDivisor(4, 1);
  glVertexAttribDivisor(5, 1);
  VBO.Unbind();

#pragma endregion

  Onix::Texture dirtText("./dirt.png");
  dirtText.Generate(GL_RGBA, GL_RGBA);

  float x = 0.0f;
  float last{};
  bool op = false;
  float speed = 0.01;
  bool dm = false;
  std::vector<float> history;
  float rgb[3] = {1.0f, 1.0f, 1.0f};
  bool dbg{};
  while (!glfwWindowShouldClose(MainWindow.Get())) {
    if(argc == 1) {
      dbg = false;
    } else if(argc > 1) {
      dbg = true;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();;
    Program.UseProgram();
    float curr = (float)glfwGetTime(), delta = curr - last;
    last = curr;
    if (glfwGetKey(MainWindow.Get(), GLFW_KEY_D) == GLFW_PRESS) {
      x += speed * delta;
    }
    if(glfwGetKey(MainWindow.Get(), GLFW_KEY_A) == GLFW_PRESS) {
      x -= speed * delta;
    }
    history.push_back(x);
    float quad_sizes = 1.0f;
    glm::vec3 pos1 = glm::vec3( x, 0.0f, 0.0f );
    Onix::Collision2D_Rect_t firstplayer { pos1.x, pos1.y, quad_sizes, quad_sizes };
    Onix::Collision2D_Rect_t secondplayer { 0.0f, 0.0f, quad_sizes, quad_sizes };
    bool res_coll = Onix::IsCollided(firstplayer, secondplayer);
    MODEL_MATRICES[0] = glm::translate(MODEL_MATRICES[0], pos1);
    glBindBuffer(GL_ARRAY_BUFFER, Instanced.Get()); // Replace with your actual buffer ID
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::mat4), &MODEL_MATRICES[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    int maxx, maxy;
    glfwGetWindowSize(MainWindow.Get(), &maxx, &maxy);
    glViewport(0, 0, maxx, maxy);

    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);
    proj = glm::perspective(glm::radians(100.0f), (float)maxx/(float)maxy, 0.1f, 100.f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    GLuint Projection_Location = glGetUniformLocation(Program.GetHandle(), "proj");
    GLuint View_Location = glGetUniformLocation(Program.GetHandle(), "view");
    glUniformMatrix4fv(Projection_Location, 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(View_Location, 1, GL_FALSE, &view[0][0]);


    VAO.Bind();
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 10);
    glBindVertexArray(0);

    #pragma region IMGUI
    
    if(dm)
      ImGui::ShowDemoWindow(&dm);
    if(dbg == true) {
      ImGuiStyle& styles = ImGui::GetStyle();
      styles.FrameRounding = 4.0f;
      styles.FrameBorderSize = 1.5f;
      ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_FirstUseEver);
      ImGui::SetNextWindowSize(ImVec2(270.0f, 900.0f), ImGuiCond_FirstUseEver);
      ImGui::Begin("Onix Debugger", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);
      ImGui::SetWindowFontScale(1.3f);
      ImGui::Text("you can change the following value");
      ImGui::Text("Onix::IsColliding() = %d", res_coll);
      ImGui::SliderFloat("##1", &delta, 0.0f, 9.0f, "VALUE: %.5f");
      //ImGui::ProgressBar(delta, ImVec2(200.0f, 20.0f));
      ImGui::SliderFloat("##", &speed, -5.0f, 5.0f, " = %.9f");
      ImGui::PlotLines("##", &history[0], history.size(), 0, NULL, FLT_MIN, FLT_MAX, ImVec2(0, 80));
      if(ImGui::Button("Change Background Color"))
        ImGui::OpenPopup("colorpicker");
      if(ImGui::BeginPopup("colorpicker")) {
        ImGui::ColorPicker4("Clear Screen Color", rgb);
        ImGui::End();
      }
      if(ImGui::Button("Show Demo Window"))
        dm = true;
      ImGui::End();
    }
    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    #pragma endregion

    glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
    glfwSwapBuffers(MainWindow.Get());
    glfwPollEvents();

  }
  glDeleteProgram(Program.GetHandle());
  glfwDestroyWindow(MainWindow.Get());
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}
