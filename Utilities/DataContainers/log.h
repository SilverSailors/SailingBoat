#ifndef SAILINGBOAT_UTILITIES_DATACONTAINERS_LOG_H_
#define SAILINGBOAT_UTILITIES_DATACONTAINERS_LOG_H_
#include <string>

class Log {
 public:
  Log();
  int entry_id;
  double bearing;
  double latitude;
  double longitude;
  double speed;
  std::string timestamp;
  double distance_from_waypoint;
  double distance_from_destination;
};

#endif // SAILINGBOAT_UTILITIES_DATACONTAINERS_LOG_H_
