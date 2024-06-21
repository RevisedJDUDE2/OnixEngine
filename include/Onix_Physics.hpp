#pragma once
#include "Onix.hpp"

namespace Onix {
  typedef struct Collision2D_Rect {
    float pos_x;
    float pos_y;
    float body_width;
    float body_height;
  } Collision2D_Rect_t;
  bool IsCollided(const Collision2D_Rect_t& first, const Collision2D_Rect_t& second);
}
