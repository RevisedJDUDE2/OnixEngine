#include "Shader.hpp"
#include <sstream>
#include <cstring>
#include <stdio.h>

Onix::Shader::Shader(const std::string& Filename, GLenum Type) {
  //Why???
  std::ifstream Source(Filename.c_str());
  if (Source.is_open()) {
    std::stringstream ShaderStringStream;
    ShaderStringStream << Source.rdbuf();
    ShaderStringStream.str().append("\0");
    size_t Buffer_Size = ShaderStringStream.str().size() + 1;
    char* Buffer = new char[Buffer_Size];
    strcpy(Buffer, ShaderStringStream.str().c_str());
    this->m_Contents = Buffer;
    this->m_Handle = glCreateShader(Type);
    glShaderSource(this->m_Handle, 1, &this->m_Contents, nullptr);
    glCompileShader(this->m_Handle);
  } else {
    Onix::ThrowError("File (" + Filename + ") Does not exist");
  }
}

Onix::Shader::Shader(GLenum Type, Onix::Shader Vertex, Onix::Shader Fragment) {
  if (Type == GL_TYPE_EX_SHADER_PROGRAM) {
    this->m_Handle = glCreateProgram();
    glAttachShader(this->m_Handle, Vertex.GetHandle());
    glAttachShader(this->m_Handle, Fragment.GetHandle());
    glLinkProgram(this->m_Handle);
    glUseProgram(this->m_Handle);
  }
}

GLuint Onix::Shader::GetHandle(void) const {
  return this->m_Handle;
}

void Onix::Shader::UseProgram(void) const {
  glUseProgram(this->m_Handle);
}

void Onix::Shader::CheckError(void) const {
  int ERRORS;
  char BUFFER[513];
  memset(BUFFER, '\0', sizeof(BUFFER));
  glGetShaderiv(this->m_Handle, GL_COMPILE_STATUS, &ERRORS);
  if (!ERRORS) {
    glGetShaderInfoLog(this->m_Handle, 512, nullptr, BUFFER);
    Onix::ThrowError(BUFFER, "[SHADER ERROR]");
  }
}
