#ifndef SAILINGBOAT_CORE_LOGGER_LOGGER_H_
#define SAILINGBOAT_CORE_LOGGER_LOGGER_H_
#include <string>
#include "../../Utilities/DataContainers/log.h"
#include "../../Utilities/DataContainers/gps_position.h"
#include "../../Hardware/GPS/gps_data.h"

class Logger {
 public:
  Logger(std::string path);
  void LogData(Log packet);
  void Publish();
  void Write(std::string message);
  void PublishWaypoint(GPSData from, GPSPosition to, std::string message);
 private:
  int entries_;
  Log log_;
  std::string file_path_;
  bool available_;
};

#endif // SAILINGBOAT_CORE_LOGGER_LOGGER_H_
