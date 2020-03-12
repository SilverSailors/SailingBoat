#include "vec2.hpp"

Vec2::Vec2() {
  x = 0;
  y = 0;
}

Vec2 Vec2::operator-(const Vec2 &v) {
  Vec2 vec;
  vec.x = this->x - v.x;
  vec.y = this->y - v.y;
  return vec;
}
