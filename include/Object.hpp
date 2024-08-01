#pragma once
#include "Essentials.hpp"

struct Object {
  void(*GetParent)(void);
};
typedef Object ObjectType;
void object_init(ObjectType* obj);
