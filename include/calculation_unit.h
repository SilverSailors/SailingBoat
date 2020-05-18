#ifndef SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#define SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#include "DataContainers/gps_data.h"
#include <glm/glm.hpp>

class CalculationUnit {
 public:
  /**
   * Constructor, initializes threshold values
   * @param rudder_upper_threshold Rudder upper threshold
   * @param sail_upper_threshold Sail upper threshold
   */
  CalculationUnit(int rudder_upper_threshold, int sail_upper_threshold);
  /**
   * Sailing controller
   * @param set_waypoint_1 First waypoint
   * @param set_waypoint_2 Second waypoint
   * @param set_boat_pos Boat position
   * @param set_wind_angle Wind direction
   * @param set_boat_heading Boat sail direction
   */
  void Controller(const GPSData &set_waypoint_1,
                  const GPSData &set_waypoint_2,
                  const GPSData &set_boat_pos,
                  int set_wind_angle,
                  int set_boat_heading);
  /**
   * Converts given degrees to radians format
   * @param degrees Degrees value
   * @return Value in radians
   */
  static double DegreesToRadians(double degrees);
  /**
   * Converts GPS coordinates to cartesian format
   * @param waypoint GPS position
   * @return Cartesian value
   */
  static glm::dvec3 GPSToCartesian(const GPSData &waypoint);
  /**
   * Normalizes degrees to between 0 and 360
   * @param degrees Degrees value
   * @return Normalized value
   */
  static int NormalizeDegrees(int sign);
  /**
   * Returns value depending on sign value
   * @param sign Sign as a number
   * @return -1 or +1
   */
  static int Sign(double sign);
  /**
   * Converts given from-, to- and position-coordinates to double
   * @param from_low From low
   * @param from_high From high
   * @param to_low To low
   * @param to_high To high
   * @param position Position
   * @return Conversion result
   */
  static double ConvertCoordinates(double from_low, double from_high,
                                   double to_low, double to_high, double position);
  /**
   * Calculates the distance between the two positions
   * @param waypoint_1 First waypoint
   * @param waypoint_2 Second waypoint
   * @return Distance between the waypoints
   */
  static double CalculateDistance(const GPSData &waypoint_1, const GPSData &waypoint_2);
  /**
   * Returns "rudder_angle_" member field value
   * @return "rudder_angle_" value
   */
  double GetRudderAngle();
  /**
   * Returns "sail_angle_" member field value
   * @return "sail_angle_" value
   */
  double GetSailAngle();
 private:
  /**
   * Favored tack
   */
  double favored_tack_ = 0;
  /**
   * Rudder angle
   */
  double rudder_angle_;
  /**
   * Sail angle
   */
  double sail_angle_;
  /**
   * Rudder max angle
   */
  int rudder_max_angle_;
  /**
   * Sail max angle
   */
  int sail_max_angle_;
};

#endif // SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
