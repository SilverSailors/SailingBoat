#ifndef __LOG_HPP__
#define __LOG_HPP__
#include <string>

class LOG {
 public:
  LOG();
  int m_entry_id;
  double m_bearing;
  double m_latitude;
  double m_longitude;
  double m_speed;
  std::string m_timestamp;
  double m_distance_from_waypoint;
  double m_distance_from_destination;

 private:
};

#endif//__LOG_HPP__
