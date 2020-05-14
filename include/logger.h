#ifndef SAILINGBOAT_INCLUDE_LOGGER_H_
#define SAILINGBOAT_INCLUDE_LOGGER_H_
#include <string>
#include "DataContainers/log.h"
#include "DataContainers/gps_data.h"
#include <ctime>
#include "json.hpp"

class Logger {
 public:
  /**
   * The constructor, initializes member fields
   * @param path File path
   */
  Logger(std::string path);
  /**
   * Saves log packet to "log_" member field
   * @param packet Log object
   */
  void LogData(const Log &packet);
  /**
   * Publishes "log_" member field data by writing it to file
   */
  void Publish();
  /**
   * Publishes from and to GPSData by writing it to file
   * @param from From coordinates
   * @param to To coordinates
   * @param message Data to write
   */
  void PublishWaypoint(const GPSData &from, const GPSData &to, const std::string &message);
 private:
  /**
   * Log info object
   */
  Log log_;
  /**
   * File path for reading and writing
   */
  std::string file_path_;
  /**
   * Available to publish data
   */
  bool available_;
};

#endif // SAILINGBOAT_INCLUDE_LOGGER_H_
