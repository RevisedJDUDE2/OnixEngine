#pragma once
#include "Onix.hpp"

namespace Onix {
  class Window {
    GLFWwindow* m_Handle;
    int m_OriginalSizeWidth, m_OriginalSizeHeight;
  public:
    Window(std::string title, int width, int height);
    ~Window();
    GLFWwindow* Get(void) const;
    int ShouldClose(void) const;
    bool isKeyPressed(int glfw_key);
    void SetFullscreen(bool condition);
  };
}
