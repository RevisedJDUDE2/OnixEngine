#pragma once
#include "Essentials.hpp"
namespace Onix {
  class Buffer {
  private:
    unsigned int m_Handle;
    GLenum m_Type;
  public:
    Buffer(GLenum Type, GLsizeiptr Size, GLvoid* Data, GLenum Usage);
    void Bind(void);
    void Unbind(void);
    unsigned int GetHandle(void);
    void DeleteBuffer(void);
  };
  class VertexArray {
  private:
    unsigned int m_Handle;
  public:
    VertexArray();
    void Bind(void);
    void Unbind(void);
    void DeleteVertexArray(void);
  };
}
