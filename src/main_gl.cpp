#include "Onix.hpp"
#include "Object.hpp"

const float version = 2.1;

int main() {
  printf("Game Version %.1f\n", version);
  const std::string resource_folder = "./resources/";
  const char* res_folder = "./resources/";
  Onix::Init_GLFW();
  Onix::Window window("Game", 800, 600);
  window.SetHint(GLFW_RESIZABLE, GLFW_FALSE);
  Onix::Init_GLAD();
  //LOAD SHADERS AND CAPTURE ERRRORS
  Onix::Shader VertexShader(resource_folder + "shader.vert", GL_VERTEX_SHADER);
  VertexShader.CheckError();
  Onix::Shader FragmentShader(resource_folder + "shader.frag", GL_FRAGMENT_SHADER);
  FragmentShader.CheckError();
  //GL_TYPE_EX_SHADER_PROGRAM is my own #define not opengls
  Onix::Shader Program(GL_TYPE_EX_SHADER_PROGRAM, VertexShader, FragmentShader);
  Program.CheckError();

  float RectangleMesh[] = {
    //coord      texture coord
    -0.5, -0.5, 0.0, 0.0,  
     0.5, -0.5, 1.0, 0.0,
     0.5,  0.5, 1.0, 1.0,
    -0.5,  0.5, 0.0, 1.0
  };

  unsigned int Indices[6] = {
      0, 1, 2,
      2, 3, 0
  };

  glm::vec2 positions[2] = {};

  unsigned int InstancedVBO;
  glGenBuffers(1, &InstancedVBO);
  glBindBuffer(GL_ARRAY_BUFFER, InstancedVBO);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW);
  
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

  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, InstancedVBO);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
  glVertexAttribDivisor(2, 1);

  char DIRT_[100];
  int imageWidth, imageHeight, imageChannels;
  strcpy(DIRT_, res_folder);
  strcat(DIRT_, "dirt.jpg");
  unsigned char* imageHandle = stbi_load((const char*)DIRT_, &imageWidth, &imageHeight, &imageChannels, 0);

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
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  float QuadMesh[] = {
    -1.0, -1.0, 1.0, 0.0, 0.0,
     1.0, -1.0, 0.0, 1.0, 0.0,
     1.0,  1.0, 0.0, 0.0, 1.0,

     1.0,  1.0, 0.0, 0.0, 1.0,
    -1.0,  1.0, 0.0, 1.0, 0.0,
    -1.0, -1.0, 1.0, 0.0, 0.0
  };

  Onix::Shader CatVertexShader(resource_folder + "cat.shader.vert", GL_VERTEX_SHADER);
  CatVertexShader.CheckError();
  Onix::Shader CatFragmentShader(resource_folder + "cat.shader.frag", GL_FRAGMENT_SHADER);
  CatFragmentShader.CheckError();
  Onix::Shader CatShaderProgram(GL_TYPE_EX_SHADER_PROGRAM, CatVertexShader, CatFragmentShader);
  CatShaderProgram.CheckError();

  ObjectType cat;
  object_init(&cat);
  cat.GetParent(&cat);
  cat.CreateObject(&cat);
  cat.SetVboData(&cat, GL_ARRAY_BUFFER, sizeof(QuadMesh), QuadMesh, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void**)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void**)(2 * sizeof(float)));
  glEnableVertexAttribArray(1);
  cat.Unbind(&cat);

  float lasttime = (float)glfwGetTime(), currenttime, delta;
  bool Show_Game = false, Show_Menu = true;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  while (!window.ShouldClose()) {

    Onix::ClearColorAndSet(0.0, 0.0, 0.0);
    if (Show_Game == true) {
      Program.UseProgram();

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, textureHandle);

      glBindVertexArray(VAO);

      glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 2);

      currenttime = (float)glfwGetTime();
      delta = currenttime - lasttime;
      lasttime = currenttime;

      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 proj = glm::mat4(1.0f);
      float coord[2] = { 0.0, 0.0 };
      view = glm::translate(view, glm::vec3(-positions[0].x, -positions[0].y, -3.0f));
      proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 100.0f);
      int maxx, maxy;
      glfwGetWindowSize(window.Get(), &maxx, &maxy);
      glViewport(0, 0, maxx, maxy);
      unsigned int viewloc = glGetUniformLocation(Program.GetHandle(), "view");
      unsigned int projloc = glGetUniformLocation(Program.GetHandle(), "proj");
      glUniformMatrix4fv(viewloc, 1, GL_FALSE, &view[0][0]);
      glUniformMatrix4fv(projloc, 1, GL_FALSE, &proj[0][0]);

      if (window.isKeyPressed(GLFW_KEY_D))
        positions[0].x += 0.5f * delta;
      if (window.isKeyPressed(GLFW_KEY_A))
        positions[0].x -= 0.5f * delta;
      if (window.isKeyPressed(GLFW_KEY_S))
        positions[0].y -= 0.5f * delta;
      if (window.isKeyPressed(GLFW_KEY_W))
        positions[0].y += 0.5f * delta;
      if (window.isKeyPressed(GLFW_KEY_SPACE))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      if (window.isKeyPressed(GLFW_KEY_ENTER))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      glBindBuffer(GL_ARRAY_BUFFER, InstancedVBO);
      glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(glm::vec2), positions);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    if (Show_Menu == true) {
      CatShaderProgram.UseProgram();
      glUniform1f(glGetUniformLocation(CatShaderProgram.GetHandle(), "alpha"), 0.5);
      cat.Bind(&cat);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      if (window.isKeyPressed(GLFW_KEY_TAB)) {
        Show_Game = true;
        Show_Menu = false;
      }
      cat.Unbind(&cat);
    }

    glfwSwapBuffers(window.Get());
    glfwPollEvents();
  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  return 0;
}