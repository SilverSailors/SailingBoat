#include "utilities.hpp"
#include <math.h>
#include <iostream>
#define EPSILON 1e-14

double Utilities::degrees_to_radians(double degrees) {
  return degrees * (M_PI / 180);
}

double Utilities::radians_to_degrees(double radians) {
  return radians * (180 / M_PI);
}

double Utilities::convert_coordinates(double from_low,
                                      double from_high,
                                      double to_low,
                                      double to_high,
                                      double position) {
  double percentile = (position - from_low) / (from_high - from_low);
  double result = percentile * (to_high - to_low) + to_low;
  return result;
}

VEC2 Utilities::degrees_to_vector(double value) {
  //Convert our degrees to radians
  //(cos & sin uses radians for its calculations)
  double radians = degrees_to_radians(value);

  VEC2 vec;
  //We inverse x so it matches our rotation (Right + | Left -)
  vec.x = -cos(radians);
  vec.y = sin(radians);

  //PI/2 gives a value very close to 0 (1e-17 etc)
  if (std::abs(vec.x) < EPSILON) vec.x = 0;
  if (std::abs(vec.y) < EPSILON) vec.y = 0;

  return vec;
}

double Utilities::vector_to_degrees(VEC2 vector) {
  //TODO
  //A = atan2(V.y, V.x)
  return 0;
}

double Utilities::coordinates_to_degrees(double lat1, double lon1, double lat2, double lon2) {
  /*
  double la1 = degrees_to_radians(lat1);
  double la2 = degrees_to_radians(lat2);
  double c = atan2(sin(degrees_to_radians(lon2-lon1))*cos(la2), cos(la1)*sin(la2) - cos(la2)*sin(la1)*cos(degrees_to_radians(lon2-lon1)));
  return radians_to_degrees(c);
  */

  double dy = lat2 - lat1;
  double dx = cos(M_PI / 180 * lat1) * (lon2 - lon1);
  double angle = atan2f(dy, dx);
  double degrees = radians_to_degrees(angle);
  //Add the offset so 0 is north
  degrees -= 90;

  //Add 360 if we are under 0 to give us a range between 0-360
  while (degrees < 0) {
    degrees += 360;
  }

  //Inverse it
  degrees = abs(degrees - 360);

  return degrees;
}

double Utilities::flip_degrees(double degrees) {
  if (degrees == 0) return 0;

  return abs(degrees - 360);
}

GPS_POSITION Utilities::extract_position_from_data(GPS_DATA data) {
  GPS_POSITION position;
  position.latitude = data.get_latitude();
  position.longitude = data.get_longitude();
  return position;
}

double Utilities::normalize(double degrees) {
  double result = degrees;
  while (result > 360) {
    result -= 360;
  }

  while (result < 0) {
    result += 360;
  }
  return result;
}