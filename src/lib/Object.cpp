#include "Object.hpp"

void object_get_parent(ObjectType* mobj) {
  std::cout << "[ONIX] Object->GetParent not implemented yet!\n";
};

//typedef void(*SetVaoFunc)(struct Object* mobj, unsigned int* VAO);
void object_create_object(ObjectType* mobj) {
  glGenVertexArrays(1, &mobj->VAO);
  glBindVertexArray(mobj->VAO);
};
//typedef void(*SetVboDataFunc)(struct Object* mobj, GLenum type, GLsizeiptr size, GLvoid* data, GLenum usage);
void object_set_vbo_data(ObjectType* mobj, GLenum type, GLsizeiptr size, GLvoid* data, GLenum usage) {
  glGenBuffers(1, &mobj->VBO);
  glBindBuffer(type, mobj->VBO);
  glBufferData(type, size, data, usage);
  mobj->Vbo_Type = type;
  mobj->Vbo_Size = size;
  mobj->Vbo_Data = data;
  mobj->Vbo_UsageType = usage;
}
//typedef void(*UnbindResourcesFunc)(struct Object* mobj);
void object_unbind_resources(ObjectType* mobj) {
  glBindBuffer(mobj->Vbo_Type, 0);
  glBindVertexArray(0);
}
//typedef void(*BindResourcesFunc)(struct Object* mobj);
void object_bind_resources(ObjectType* mobj) {
  glBindVertexArray(mobj->VAO);
}
void object_init(ObjectType* obj) {
  obj->GetParent = object_get_parent;
  obj->CreateObject = object_create_object;
  obj->SetVboData = object_set_vbo_data;
  obj->Unbind = object_unbind_resources;
  obj->Bind = object_bind_resources;
  obj->VBO = 0;
  obj->VAO = 0;
}