#include "Buffers.hpp"
#include "Buffers.hpp"
#include "Buffers.hpp"
#include "Buffers.hpp"
#include "Onix.hpp"
#include <iostream>
Onix::Buffer::Buffer(GLenum Type, GLsizeiptr Size, GLvoid* Data, GLenum Usage) {
  if (Type != 0 || Type != NULL) {
    glGenBuffers(1, &this->m_Handle);
    Onix::CheckGLError("Onix::Buffer::Buffer Inside after glGenBuffers");
    this->Bind();
    glBufferData(Type, Size, Data, Usage);
    Onix::CheckGLError("Onix::Buffer::Buffer Inside after glBufferData");
  } else {
    Onix::ThrowError("Onix::Buffer::Buffer(GLenum Type...) -> Type is eitheir 0 or NULL");
  }
}
void Onix::Buffer::Bind(void) {
  glBindBuffer(this->m_Type, this->m_Handle);
  Onix::CheckGLError("Onix::Buffer::Bind()");
}
void Onix::Buffer::Unbind(void) {
  glBindBuffer(this->m_Type, 0);
  Onix::CheckGLError("Onix::Buffer::Unbind()");
}
unsigned int Onix::Buffer::GetHandle(void) {
  return this->m_Handle;
}
void Onix::Buffer::DeleteBuffer(void) {
  glDeleteBuffers(1, &this->m_Handle);
}
//VAO
Onix::VertexArray::VertexArray() {
  glGenVertexArrays(1, &this->m_Handle);
  this->Bind();
}

void Onix::VertexArray::Bind(void) {
  glBindVertexArray(this->m_Handle);
}

void Onix::VertexArray::Unbind(void) {
  glBindVertexArray(0);
}

void Onix::VertexArray::DeleteVertexArray(void) {
  glDeleteVertexArrays(1, &this->m_Handle);
}
