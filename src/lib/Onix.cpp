#include "Onix.hpp"
#include "Buffers.hpp"

void Onix::Assert(bool STATEMENT, int LINE_NUM, const char* FILE) {
  if (!STATEMENT) {
    Onix::ThrowError("Onix::Assert Failed! At Line: " + std::to_string(LINE_NUM) + " File: " + FILE);
  }
}

void Onix::ThrowError(std::string ErrorMessage) {
  std::cout << "[ERROR]: " << ErrorMessage << std::endl;
}

void Onix::ThrowError(std::string ErrorMessage, std::string type) {
  std::cout << ErrorMessage << ErrorMessage << std::endl;
}

void Onix::Init_GLFW(void) {
  if (!glfwInit()) {
    //Onix::ThrowError("Opengl was not supported on your device.", "[DEBUG]");
    throw std::runtime_error("OpenGL was not supported on your device!");
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
void Onix::SetVertexAttribPointer(bool isEnabled, int Index, int Count, GLsizei Stride, const GLvoid* Offset) {
  if (isEnabled == true) {
    glVertexAttribPointer(Index, Count, GL_FLOAT, GL_FALSE, Stride, Offset);
  } else {
    Onix::EnableVertexAttrib(Index);
    glVertexAttribPointer(Index, Count, GL_FLOAT, GL_FALSE, Stride, Offset);
  }
}

bool Onix::EnableVertexAttrib(int Index) {
  glEnableVertexAttribArray(Index);
  return true;
}

void Onix::ClearColorAndSet(float r, float g, float b) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(r, g, b, 1.0f);
}

void Onix::CheckGLError(const std::string& msg) {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    Onix::ThrowError("OpenGL Error After: " + msg + " >> " +std::to_string(err));
  }
}

READ_ONLY Onix::SwapBuffersAndPollEvents(ONIX_PARAMTYPE_WINDOW window) {
  /*
  glfwSwapBuffers(window.Get());
  glfwPollEvents();
  */
  return IS_EXPERIMENTAL_FUNCTION;
}
