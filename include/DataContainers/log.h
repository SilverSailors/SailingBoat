#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
#include <string>

struct Log {
  /**
   * Log entry
   */
  int entry_id;
  /**
   * Current boat latitude coordinate
   */
  double latitude;
  /**
   * Current boat longitude coordinate
   */
  double longitude;
  /**
   * Destination latitude coordinate
   */
  double destination_latitude;
  /**
   * Destination longitude coordinate
   */
  double destination_longitude;
  /**
   * Destination distance
   */
  double destination_distance;
  /**
   * Wind direction
   */
  int wind_angle;
  /**
   * Boat sailing direction
   */
  int boat_heading;
  /**
   * Distance between boat and line in meters
   */
  double boat_to_line_distance;
  /**
   * Favored tack
   */
  double favored_tack;
  /**
   * Angle between line and east
   */
  double angle_of_line;
  /**
   * Nominal angle
   */
  double nominal_angle;
  /**
   * Preferred sailing direction
   */
  double route_angle;
  /**
   * Angle of rudder
   */
  double rudder_angle;
  /**
   * Angle of sail
   */
  double sail_angle;
  /**
   * Timestamp
   */
  std::string timestamp;
};

#endif // SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
