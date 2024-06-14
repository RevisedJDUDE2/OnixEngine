#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#ifdef USE_HEADERS
#include "Window.hpp"
#include "Buffers.hpp"
#include "Shader.hpp"
#endif

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
}