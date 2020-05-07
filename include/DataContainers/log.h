#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
#include <string>

struct Log {
  /**
   * Log entry
   */
  int entry_id;
  /**
   * Latitude coordinate
   */
  double latitude;
  /**
   * Longitude coordinate
   */
  double longitude;
  /**
   * Wing angle
   */
  int wind_angle;
  /**
   * Boat heading
   */
  int boat_heading;
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
   * Route angle
   */
  double route_angle;
  /**
   * Rudder angle
   */
  double rudder_angle;
  /**
   * Sail angle
   */
  double sail_angle;
  /**
   * Timestamp
   */
  std::string timestamp;
};

#endif // SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
