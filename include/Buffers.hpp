#pragma once
#include "Essentials.hpp"

namespace Onix {
  class Buffer {
    unsigned int m_Handle;
    GLenum m_Type = 0; //DEFAULT VAL
    /**@brief this variable sets true if we called this->[void]InitBuffer(void)*/
    bool hsntbuff;
    /**@brief tells to NOT automatically bind the current buffer on Buffer() called*/
    bool automaticBinding = false;
    /**@brief tells the Onix::EnableVertexAttrib to enable at index */
    /**DEPRECATED_FUNCTION
    bool m_has_called_enable = false;**/
    /**@brief tells opengl to set is vao so when we call bind it is automatics*/
    bool isVao;
  public:
    /** @brief basically its just glGenBuffers()*/
    void InitBuffer(void);
    Buffer(bool isVao = false) noexcept;
    Buffer(GLenum Type, GLsizeiptr Size, const GLvoid* Data, GLenum Usage) noexcept;
    void Bind(void) const;
    void Unbind(void) const;
    /**@brief a function to set the automaticBinding to true or false*/
    void SetConfigs(int i, bool CONFIG);
    //FUNCTIONS BELLOW IS DEPRECATED
    //void SetCalled(bool c);
    //bool GetStatus(void) const;
    //
    unsigned int Get(void) const noexcept;
  };
}