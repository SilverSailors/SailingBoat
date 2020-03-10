#include "VEC2.hpp"

VEC2::VEC2() {
  x = 0;
  y = 0;
}

VEC2 VEC2::operator-(const VEC2 &v) {
  VEC2 vec;
  vec.x = this->x - v.x;
  vec.y = this->y - v.y;
  return vec;
}
