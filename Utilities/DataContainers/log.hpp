#ifndef __LOG_HPP__
#define __LOG_HPP__
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

#endif //__LOG_HPP__
