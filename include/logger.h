#ifndef SAILINGBOAT_INCLUDE_LOGGER_H_
#define SAILINGBOAT_INCLUDE_LOGGER_H_
#include <string>
#include <ctime>
#include "DataContainers/log.h"
#include "json.hpp"

//TEMP
class GPSData {
  public:
    double latitude;
    double longitude;
    std::string time;
    double GetLongitude(){return longitude;};
    double GetLatitude(){return latitude;};
    std::string GetTime(){return time;};
};

class GPSPosition {
  public:
    double latitude;
    double longitude;
};
//TEMP

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

#endif // SAILINGBOAT_INCLUDE_LOGGER_H_
