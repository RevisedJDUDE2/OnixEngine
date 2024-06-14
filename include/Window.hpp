#pragma once
#include "Onix.hpp"

namespace Onix {
  class Window {
    GLFWwindow* m_Handle;
  public:
    Window(std::string title, int width, int height);
    ~Window();
    GLFWwindow* Get(void) const;
  };
}
