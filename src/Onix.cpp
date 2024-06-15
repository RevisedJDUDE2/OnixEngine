#include "Onix.hpp"
#include "Buffers.hpp"

void Onix::ThrowError(std::string ErrorMessage) {
  std::cout << "[ERROR]: " << ErrorMessage << std::endl;
}

void Onix::ThrowError(std::string ErrorMessage, std::string type) {
  std::cout << ErrorMessage << ErrorMessage << std::endl;
}

void Onix::Init_GLFW(void) {
  if (!glfwInit()) {
    Onix::ThrowError("Opengl was not supported on your device.", "[DEBUG]");
  }
}
#ifdef USE_GLAD
void Onix::Init_GL(void) {
  if (glewInit() != GLEW_OK) {
    Onix::ThrowError("OpenGL Renderer Failed to init");
  }
}
#endif

void Onix::Init_GLAD(void) {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Oh you're fucked\n");
  }   
}

void Onix::SetVertexAttribPointer(int Index, int Count, GLsizei Stride, const GLvoid* Offset) {
  glVertexAttribPointer(Index, Count, GL_FLOAT, GL_FALSE, Stride, Offset);
  glEnableVertexAttribArray(Index);
}

void Onix::SetVertexAttribPointer(Onix::Buffer& buff, int Index, int Count, GLsizei Stride, const GLvoid* Offset) {
  glVertexAttribPointer(Index, Count, GL_FLOAT, GL_FALSE, Stride, Offset);
  if(buff.GetStatus() != true) {
    glEnableVertexAttribArray(Index);
  }
}

void Onix::EnableVertexAttrib(Onix::Buffer& buff, int Index) {
  buff.SetCalled(true);
  glEnableVertexAttribArray(Index);
}