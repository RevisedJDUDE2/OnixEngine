#include "Window.hpp"
#include "Window.hpp"
#include "Window.hpp"
#include "Window.hpp"

Onix::Window::Window(std::string title, int width, int height) {
  this->m_Handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!this->m_Handle) {
    Onix::ThrowError("Window was nullptr");
  }
  glfwMakeContextCurrent(this->m_Handle);
  this->m_OriginalSizeHeight = height;
  this->m_OriginalSizeWidth = width;
}

Onix::Window::~Window() {
  glfwDestroyWindow(this->m_Handle);
  glfwTerminate();
}

GLFWwindow* Onix::Window::Get(void) const {
  return this->m_Handle;
}

int Onix::Window::ShouldClose(void) const {
  return glfwWindowShouldClose(this->m_Handle);
}

bool Onix::Window::isKeyPressed(int glfw_key) {
  if (glfwGetKey(this->m_Handle, glfw_key) == GLFW_PRESS) {
    return true;
  }
  return false;
}

void Onix::Window::SetFullscreen(bool condition) {
  const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  if (condition) { // if window.isKeyPressed(...) SetFullscreen(!is) auto mated stop;
      glfwSetWindowAttrib(this->m_Handle, GLFW_DECORATED, GLFW_FALSE);
      glfwSetWindowAttrib(this->m_Handle, GLFW_RESIZABLE, GLFW_FALSE);
      glfwSetWindowSize(this->m_Handle, mode->width, mode->height);
      glfwSetWindowPos(this->m_Handle, 0, 0);
      glfwSetWindowAttrib(this->m_Handle, GLFW_FLOATING, GLFW_TRUE);
  } else if (condition == false) {
      glfwSetWindowSize(this->m_Handle, this->m_OriginalSizeWidth, this->m_OriginalSizeHeight);
      glfwSetWindowPos(this->m_Handle, (mode->width - this->m_OriginalSizeWidth) / 2, (mode->height - this->m_OriginalSizeHeight) / 2); //set to center
      glfwSetWindowAttrib(this->m_Handle, GLFW_DECORATED, GLFW_TRUE);
      glfwSetWindowAttrib(this->m_Handle, GLFW_RESIZABLE, GLFW_TRUE);
      glfwSetWindowAttrib(this->m_Handle, GLFW_FLOATING, GLFW_FALSE);
  }
}
