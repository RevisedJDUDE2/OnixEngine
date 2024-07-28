#include "Buffers.hpp"
#include "Buffers.hpp"
#include "Buffers.hpp"
#include "Onix.hpp"
#include "Buffers.hpp"
#include "Onix.hpp"
#include <iostream>

Onix::Buffer::Buffer(bool isVao, GLenum Type) {
  this->SIGNAL = 0; // init
  this->isVao = isVao;
  this->m_Handle = 0;
  if (isVao) {
    this->m_Type = 0;
  }
  else {
    this->m_Type = Type;
  }
}

void Onix::Buffer::SetData(GLsizeiptr Size, GLvoid* Data, GLenum Usage) {
  if (!this->isVao) {
    if (this->SIGNAL != 222)
      glGenBuffers(1, &this->m_Handle);
    this->Bind();
    glBufferData(this->m_Type, Size, Data, Usage);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      std::cout << "glBufferData Error: " << error << std::endl;
    }
  }
  else {
    if (this->SIGNAL != 222)
      glGenVertexArrays(1, &this->m_Handle);
    //this->Bind();
  }
}

void Onix::Buffer::Bind(void) const {
  if (!this->isVao) {
    glBindBuffer(this->m_Type, this->m_Handle);
    std::cout << "Bound Buffer with handle: " << this->m_Handle << std::endl;
  }
  else {
    glBindVertexArray(this->m_Handle);
    std::cout << "Bound VAO with handle: " << this->m_Handle << std::endl;
  }
}

void Onix::Buffer::Unbind(void) const {
  if (!this->isVao) {
    glBindBuffer(this->m_Type, 0);
  }
  else {
    glBindVertexArray(0);
  }
}

void Onix::Buffer::GenBuffers(void) {
  this->SIGNAL = 222;
  if (!this->isVao) {
    glGenBuffers(1, &this->m_Handle);
    std::cout << "Generated Buffer with handle: " << this->m_Handle << std::endl;
  }
  else {
    glGenVertexArrays(1, &this->m_Handle);
    std::cout << "Generated VAO with handle: " << this->m_Handle << std::endl;
  }
}

unsigned int Onix::Buffer::GetHandle(void) const {
  return this->m_Handle;
}

void Onix::Buffer::SendSignal(int SIG) {
  this->SIGNAL = SIG;
}

int Onix::Buffer::GetSignal(void) {
  return this->SIGNAL;
}
