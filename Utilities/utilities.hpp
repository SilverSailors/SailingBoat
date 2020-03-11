#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__
#include "DataContainers/vec2.hpp"
#include "DataContainers/gps_position.hpp"
#include "../Hardware/Gps/gps_data.hpp"

class Utilities {
 public:
  static double DegreesToRadians(double degrees);
  static double RadiansToDegrees(double radians);
  static double ConvertCoordinates(double from_low, double from_high, double to_low, double to_high, double position);
  static Vec2 DegreesToVector(double value);
  static double VectorToDegrees(Vec2 vector);
  static double CoordinatesToDegrees(double lat1, double lon1, double lat2, double lon2);
  static double FlipDegrees(double degrees);
  static GpsPosition ExtractPositionFromData(GpsData data);
  static double Normalize(double degrees);
};

#endif //__UTILITIES_HPP__
