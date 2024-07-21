#pragma once
#include "Essentials.hpp"

namespace Onix {
  class Buffer {
    unsigned int m_Handle;
    GLenum m_Type = 0; //DEFAULT VAL
    bool hsntbuff;
    bool automaticBinding = false;
    bool isVao = false;
    bool SpecifyCalled = false;
    void m_Create(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage);
  public:
    void InitBuffer(void);
    void Specify(bool isVao);
    Buffer();
    Buffer(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage) noexcept;
    void Bind(void) const;
    void Unbind(void) const;
    void SetConfigs(int i, bool CONFIG);
    unsigned int Get(void) const noexcept;
  };
}