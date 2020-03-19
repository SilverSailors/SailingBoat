#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_VEC2_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_VEC2_H_

class Vec2 {
 public:
  /**
   * The constructor, initializes member fields
   */
  Vec2();
  /**
   * Vector X axis
   */
  double x;
  /**
   * Vector Y axis
   */
  double y;
  /**
   * Overloaded subtraction operator
   * @param vector Vec2 object
   * @return New Vec2 object
   */
  Vec2 operator-(const Vec2 &vector);
};

#endif // SAILINGBOAT_INCLUDE_DATACONTAINERS_VEC2_H_
