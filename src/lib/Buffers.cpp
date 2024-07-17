#include "Buffers.hpp"

void Onix::Buffer::InitBuffer(void) {
  glGenBuffers(1, &this->m_Handle);
  this->hsntbuff = true;
}

Onix::Buffer::Buffer(bool isVao) noexcept {
  if (isVao) {
    this->m_Type = 0;
    glGenVertexArrays(1, &this->m_Handle);
  }
}

Onix::Buffer::Buffer(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage) noexcept {
  if (Type != 0 && this->isVao == true) {
    glGenBuffers(1, &this->m_Handle);
    glBindBuffer(Type, this->m_Handle);
    glBufferData(Type, Size, Data, Usage);
  }
  this->m_Type = Type;
}

void Onix::Buffer::Bind(void) const {
  if (this->m_Type != 0) {
    glBindBuffer(this->m_Type, this->m_Handle);
  } else {
    glBindVertexArray(this->m_Handle);
  }
}

void Onix::Buffer::Unbind(void) const {
  if (this->m_Type != 0) {
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

unsigned int Onix::Buffer::Get(void) const noexcept {
  return this->m_Handle;
}