#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Essentials.hpp"
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#define IS_EXPERIMENTAL_FUNCTION 0xF1
#define DONOT_MODIFY //THE FUNCTION DEFINED BELOW IS IMPORTANT PLEASE DONT MODIFY OR DELETE
#define DEPRECATED_FUNCTION //THE FUNCTION BELOW IS DEPRACTED!

typedef unsigned int READ_ONLY;
typedef unsigned long ONIX_PARAMTYPE_WINDOW;

typedef struct {
  float Position[3];
  float Color[3];
  float TexturePos[2];
} Vertices;
namespace Onix {
  void ThrowError(std::string ErrorMessage);
  void ThrowError(std::string ErrorMessage, std::string type);
  void Init_GLFW(void);
  void Init_GL(void);
  void Init_GLAD(void);
  void SetVertexAttribPointer(int Index, int Count, GLsizei Stride, const GLvoid* Offset);
  void SetVertexAttribPointer(Onix::Buffer& buff, int Index, int Count, GLsizei Stride, const GLvoid* Offset);
  void EnableVertexAttrib(Onix::Buffer& buff, int Index);
  void ClearColorAndSet(float r, float g, float b);
  // VS giving me weird ass errors
  READ_ONLY SwapBuffersAndPollEvents(ONIX_PARAMTYPE_WINDOW window);
}