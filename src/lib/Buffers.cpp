#include "Buffers.hpp"
#include "Onix.hpp"

void Onix::Buffer::m_Create(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage) {
  ONIX_ASSERT(this->isVao);
  if (Type != 0 && false == this->isVao && false == this->SpecifyCalled) {
    glGenBuffers(1, &this->m_Handle);
    glBindBuffer(Type, this->m_Handle);
    glBufferData(Type, Size, Data, Usage);
  } else if(this->SpecifyCalled == true && this->isVao == true) {
    glGenVertexArrays(1, &this->m_Handle);
  }
  this->m_Type = Type;
}

void Onix::Buffer::InitBuffer(void) {
  glGenBuffers(1, &this->m_Handle);
  this->hsntbuff = true;
}

void Onix::Buffer::Specify(bool isVao) {
  this->isVao = isVao;
  this->SpecifyCalled = true;
  this->m_Create(0, 0, 0, 0);
}

Onix::Buffer::Buffer() {
  this->isVao = false;
  this->SpecifyCalled = false;
  this->m_Type = 0;
}

Onix::Buffer::Buffer(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage) noexcept {
  //if (Type != 0 && false == this->isVao && false == this->SpecifyCalled) {
  //  glGenBuffers(1, &this->m_Handle);
  //  glBindBuffer(Type, this->m_Handle);
  //  glBufferData(Type, Size, Data, Usage);
  //} else if(this->SpecifyCalled == true && this->isVao == true) {
  //  glGenVertexArrays(1, &this->m_Handle);
  //}
  //this->m_Type = Type;
  this->m_Create(Type, Size, Data, Usage);
}

void Onix::Buffer::Bind(void) const {
  if (this->m_Type != 0 && false == this->isVao) {
    glBindBuffer(this->m_Type, this->m_Handle);
  } else {
    glBindVertexArray(this->m_Handle);
  }
}

void Onix::Buffer::Unbind(void) const {
  if (this->m_Type != 0 && false == this->isVao) {
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