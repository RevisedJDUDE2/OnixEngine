#include "Buffers.hpp"

void Onix::Buffer::InitBuffer(void) {
  glGenBuffers(1, &this->m_Handle);
  this->hsntbuff = true;
}

Onix::Buffer::Buffer(GLenum Type) {
  if (Type == GL_VERTEX_ARRAY) {
    this->m_Type = GL_VERTEX_ARRAY;
    glGenVertexArrays(1, &this->m_Handle);
  }
}

Onix::Buffer::Buffer(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage) {
  if (Type != GL_VERTEX_ARRAY) {
    glGenBuffers(1, &this->m_Handle);
    glBindBuffer(Type, this->m_Handle);
    glBufferData(Type, Size, Data, Usage);
  }
  this->m_Type = Type;
}

void Onix::Buffer::Bind(void) const {
  if (this->m_Type != GL_VERTEX_ARRAY) {
    glBindBuffer(this->m_Type, this->m_Handle);
  } else {
    glBindVertexArray(this->m_Handle);
  }
}

void Onix::Buffer::Unbind(void) const {
  if (this->m_Type != GL_VERTEX_ARRAY) {
    glBindBuffer(this->m_Type, 0);
  } else {
    glBindVertexArray(0);
  }
}

void Onix::Buffer::SetConfigs(int i, bool CONFIG) {
  if (i == 0) {
    this->automaticBinding = CONFIG;
  } else if (i == 1) {
    this->hsntbuff = CONFIG;
  }
};

void Onix::Buffer::SetCalled(bool c) {
  this->m_has_called_enable = c;
}

bool Onix::Buffer::GetStatus(void) const {
  return this->m_has_called_enable;
}
unsigned int Onix::Buffer::Get(void) const noexcept {
  return this->m_Handle;
}