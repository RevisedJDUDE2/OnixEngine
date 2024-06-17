#pragma once
#include "Essentials.hpp"

namespace Onix {
  class Buffer {
    unsigned int m_Handle;
    GLenum m_Type;
    /**@brief this variable sets true if we called this->[void]InitBuffer(void)*/
    bool hsntbuff;
    /**@brief tells to NOT automatically bind the current buffer on Buffer() called*/
    bool automaticBinding = false;
    /**@brief tells the Onix::EnableVertexAttrib to enable at index */
    bool m_has_called_enable = false;
  public:
    /** @brief basically its just glGenBuffers()*/
    void InitBuffer(void);
    Buffer(GLenum Type);
    Buffer(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage);
    void Bind(void) const;
    void Unbind(void) const;
    /**@brief a function to set the automaticBinding to true or false*/
    void SetConfigs(int i, bool CONFIG);
    //USAGE OF this->m_has_called_enable = c params
    void SetCalled(bool c);
    bool GetStatus(void) const;
    unsigned int Get(void) const noexcept;
  };
}