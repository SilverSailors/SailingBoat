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
