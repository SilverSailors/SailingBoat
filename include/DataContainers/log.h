#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
#include <string>

class Log {
 public:
  /**
   * The constructor, initializes member fields
   */
  Log();
  /**
   * Not in use
   */
  int entry_id;
  /**
   * Bearing
   */
  double bearing;
  /**
   * Latitude, coordinate
   */
  double latitude;
  /**
   * Longitude coordinate
   */
  double longitude;
  /**
   * Not in use
   */
  double speed;
  /**
   * Timestamp
   */
  std::string timestamp;
  /**
   * Not in use
   */
  double distance_from_waypoint;
  /**
   * Not in use
   */
  double distance_from_destination;
};

#endif // SAILINGBOAT_INCLUDE_DATACONTAINERS_LOG_H_
