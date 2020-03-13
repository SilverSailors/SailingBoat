#ifndef SAILINGBOAT_INCLUDE_UTILITIES_H_
#define SAILINGBOAT_INCLUDE_UTILITIES_H_
#include "DataContainers/vec2.h"
#include "DataContainers/gps_position.h"
#include "gps_data.h"

class Utilities {
 public:
  static double DegreesToRadians(double degrees);
  static double RadiansToDegrees(double radians);
  static double ConvertCoordinates(double from_low, double from_high, double to_low, double to_high, double position);
  static Vec2 DegreesToVector(double value);
  static double VectorToDegrees(Vec2 vector);
  static double CoordinatesToDegrees(double lat1, double lon1, double lat2, double lon2);
  static double FlipDegrees(double degrees);
  static GPSPosition ExtractPositionFromData(GPSData data);
  static double Normalize(double degrees);
};

#endif // SAILINGBOAT_INCLUDE_UTILITIES_H_
