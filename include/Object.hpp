#pragma once
#include "Essentials.hpp"

typedef void(*GetParentFunc)(struct Object* mobj);
typedef void(*CreateObjectFunc)(struct Object* mobj);
typedef void(*SetVboDataFunc)(struct Object* mobj, GLenum type, GLsizeiptr size, GLvoid* data, GLenum usage);
typedef void(*UnbindResourcesFunc)(struct Object* mobj);
typedef void(*BindResourcesFunc)(struct Object* mobj);
struct Object {
  //FUNCTIONS:
  GetParentFunc GetParent;
  CreateObjectFunc CreateObject;
  SetVboDataFunc SetVboData;
  UnbindResourcesFunc Unbind;
  BindResourcesFunc Bind;
  unsigned int VAO, VBO;
  //FOR VBO_USAGE_TYPE its GL_ STATIC | DYNAMIC _ DRAW | STREAM | COPY eg... GL_STATIC_DRAW
  GLenum Vbo_Type, Vbo_UsageType;
  GLsizeiptr Vbo_Size;
  GLvoid* Vbo_Data;
};
typedef Object ObjectType;
void object_init(ObjectType* obj);
