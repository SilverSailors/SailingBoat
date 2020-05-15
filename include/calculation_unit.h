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
   * @return New rudder and sail angles
   */
  glm::dvec2 Controller(const GPSData &set_waypoint_1,
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
  static int NormalizeDegrees(int degrees);
  /**
   * Returns value depending on sign value
   * @param sign Sign in form of number
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
   * @return Result from conversion
   */
  static double ConvertCoordinates(double from_low, double from_high,
                                   double to_low, double to_high, double position);
  /**
   * Calculates the distance between the two positions
   * @param position_1 First position
   * @param position_2 Second position
   * @return Distance between the positions
   */
  static double CalculateDistance(const GPSData &position_1, const GPSData &position_2);
 private:
  /**
   * Favored tack
   */
  double favored_tack_ = 0;
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
