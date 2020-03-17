#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_VEC2_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_VEC2_H_

class Vec2 {
 public:
  Vec2();
  double x;
  double y;
  
  ///
  ///Overloaded operators
  ///
  Vec2 operator-(const Vec2 &vector);
};

#endif // SAILINGBOAT_INCLUDE_DATACONTAINERS_VEC2_H_
