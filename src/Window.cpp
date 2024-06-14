#include "Window.hpp"

Onix::Window::Window(std::string title, int width, int height) {
  this->m_Handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!this->m_Handle) {
    Onix::ThrowError("Window was nullptr");
  }
  glfwMakeContextCurrent(this->m_Handle);
}

Onix::Window::~Window() {
  glfwDestroyWindow(this->m_Handle);
  glfwTerminate();
}

GLFWwindow* Onix::Window::Get(void) const {
  return this->m_Handle;
}
