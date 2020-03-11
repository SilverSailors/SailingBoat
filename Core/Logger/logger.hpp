#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <string>
#include "../../Utilities/Data_Containers/LOG.hpp"
#include "../../Utilities/Data_Containers/GPS_POSITION.hpp"
#include "../../Hardware/GPS/GPS_data.hpp"

class Logger {
 public:
  Logger(std::string path);
  void log_data(LOG packet);
  void publish();
  void write(std::string message);
  void publish_waypoint(GPS_DATA from, GPS_POSITION to, std::string message);

 private:
  int m_entries;
  LOG m_log;
  std::string m_file_path;
  bool m_available;
};

#endif//__LOGGER_HPP__
