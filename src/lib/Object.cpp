#include "Object.hpp"

void object_get_parent(void) {
  std::cout << "[ONIX] Object->GetParent not implemented yet!\n";
};

void object_init(ObjectType* obj) {
  obj->GetParent = object_get_parent;
}