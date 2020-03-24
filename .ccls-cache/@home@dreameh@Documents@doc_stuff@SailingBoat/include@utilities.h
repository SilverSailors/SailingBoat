#ifndef SAILINGBOAT_INCLUDE_UTILITIES_H_
#define SAILINGBOAT_INCLUDE_UTILITIES_H_
#include "DataContainers/vec2.h"
#include "DataContainers/gps_position.h"
#include "gps_data.h"

class Utilities {
 public:
  /**
   * Converts given degrees to radians format
   * @param degrees Degrees value
   * @return Value in radians
   */
  static double DegreesToRadians(double degrees);
  /**
   * Converts given radians to degrees format
   * @param radians Radians value
   * @return Value in degrees
   */
  static double RadiansToDegrees(double radians);
  /**
   * Converts given from-, to- and position-coordinates to double
   * @param from_low From low
   * @param from_high From high
   * @param to_low To low
   * @param to_high To high
   * @param position Position
   * @return Result from conversion
   */
  static double ConvertCoordinates(double from_low, double from_high, double to_low, double to_high, double position);
  /**
   * Converts given degrees to vector format
   * @param value Degrees value
   * @return Value as Vec2 object
   */
  static Vec2 DegreesToVector(double value);
  /**
   * Not in use
   * @param vector
   * @return
   */
  static double VectorToDegrees(Vec2 vector);
  /**
   * Converts given coordinates to degrees
   * @param lat1 First latitude
   * @param lon1 First longitude
   * @param lat2 Second latitude
   * @param lon2 Second longitude
   * @return Value in degrees
   */
  static double CoordinatesToDegrees(double lat1, double lon1, double lat2, double lon2);
  /**
   * Converts given degrees to positive value
   * @param degrees Degrees value
   * @return Value in positive degrees
   */
  static double FlipDegrees(double degrees);
  /**
   * Extracts position from given GPSData
   * @param data GPSData object
   * @return GPSPosition object
   */
  static GPSPosition ExtractPositionFromData(GPSData data);
  /**
   * Normalizes degrees to between 0 and 360
   * @param degrees Degrees value
   * @return Normalized value
   */
  static double Normalize(double degrees);
};

#endif // SAILINGBOAT_INCLUDE_UTILITIES_H_
