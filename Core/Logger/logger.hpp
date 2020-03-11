#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <string>
#include "../../Utilities/DataContainers/log.hpp"
#include "../../Utilities/DataContainers/gps_position.hpp"
#include "../../Hardware/Gps/gps_data.hpp"

class Logger {
 public:
  Logger(std::string path);
  void LogData(Log packet);
  void Publish();
  void Write(std::string message);
  void PublishWaypoint(GpsData from, GpsPosition to, std::string message);
 private:
  int entries_;
  Log log_;
  std::string file_path_;
  bool available_;
};

#endif //__LOGGER_HPP__
