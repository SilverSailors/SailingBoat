#include "../include/utilities.h"
#include "../test/doctest.h"
#include <math.h>
#include <iostream>
#define EPSILON 1e-14

double Utilities::DegreesToRadians(double degrees) {
  return degrees * (M_PI / 180);
}

TEST_CASE("test degrees to radians function") {
  CHECK(Utilities::DegreesToRadians(100) == doctest::Approx(1.74533));
}

double Utilities::RadiansToDegrees(double radians) {
  return radians * (180 / M_PI);
}

double Utilities::ConvertCoordinates(double from_low,
                                     double from_high,
                                     double to_low,
                                     double to_high,
                                     double position) {
  double percentile = (position - from_low) / (from_high - from_low);
  double result = percentile * (to_high - to_low) + to_low;
  return result;
}

Vec2 Utilities::DegreesToVector(double value) {
  //Convert our degrees to radians
  //(cos & sin uses radians for its calculations)
  double radians = DegreesToRadians(value);

  Vec2 vec;
  //We inverse x so it matches our rotation (Right + | Left -)
  vec.x = -cos(radians);
  vec.y = sin(radians);
  //PI/2 gives a value very close to 0 (1e-17 etc)
  if (std::abs(vec.x) < EPSILON) vec.x = 0;
  if (std::abs(vec.y) < EPSILON) vec.y = 0;

  return vec;
}

double Utilities::VectorToDegrees(Vec2 vector) {
  //TODO
  //A = atan2(V.y, V.x)
  return 0;
}

double Utilities::CoordinatesToDegrees(double lat1, double lon1, double lat2, double lon2) {
  /*
  double la1 = degrees_to_radians(lat1);
  double la2 = degrees_to_radians(lat2);
  double c = atan2(sin(degrees_to_radians(lon2-lon1))*cos(la2), cos(la1)*sin(la2) - cos(la2)*sin(la1)*cos(DegreesToRadians(lon2-lon1)));
  return RadiansToDegrees(c);
  */

  double dy = lat2 - lat1;
  double dx = cos(M_PI / 180 * lat1) * (lon2 - lon1);
  double angle = atan2f(dy, dx);
  double degrees = RadiansToDegrees(angle);
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

double Utilities::FlipDegrees(double degrees) {
  if (degrees == 0) return 0;

  return abs(degrees - 360);
}

GPSPosition Utilities::ExtractPositionFromData(GPSData data) {
  GPSPosition position;
  position.latitude = data.GetLatitude();
  position.longitude = data.GetLongitude();
  return position;
}

double Utilities::Normalize(double degrees) {
  double result = degrees;
  while (result > 360) {
    result -= 360;
  }

  while (result < 0) {
    result += 360;
  }
  return result;
}
