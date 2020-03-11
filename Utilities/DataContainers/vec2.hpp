#ifndef __VEC2_HPP__
#define __VEC2_HPP__

class Vec2 {
 public:
  Vec2();
  double x;
  double y;
  //Overloaded operators
  Vec2 operator-(const Vec2 &vector);
};

#endif //__VEC2_HPP__
