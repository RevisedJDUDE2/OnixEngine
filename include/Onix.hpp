#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Essentials.hpp"
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"

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
}