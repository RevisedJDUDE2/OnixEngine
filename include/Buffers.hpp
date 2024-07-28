#pragma once
#include "Essentials.hpp"
namespace Onix {
  class Buffer {
  private:
    unsigned int m_Handle;
    GLenum m_Type = 0;
    bool isVao;
    int SIGNAL;
  public:
    Buffer(bool isVao, GLenum Type);
    void SetData(GLsizeiptr Size, GLvoid* Data, GLenum Usage);
    void Bind(void) const;
    void Unbind(void) const;
    /** @brief it's basicaly just glGen
    */
    void GenBuffers(void);
    unsigned int GetHandle(void) const;
    void SendSignal(int SIG);
    int GetSignal(void);
  };
}