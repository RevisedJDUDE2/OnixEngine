#pragma once
#include "Onix.hpp"
#include <fstream>

#define GL_TYPE_EX_SHADER_PROGRAM 0xDEADED

namespace Onix {
  class Shader {
  private:
    unsigned int m_Handle;
    const char* m_Contents;
  public:
    Shader(const std::string& Filename, GLenum Type);
    Shader(GLenum Type, Onix::Shader Vertex, Onix::Shader Fragment);
    GLuint GetHandle(void) const;
    void UseProgram(void) const;
    void CheckError(void) const;
  };
}