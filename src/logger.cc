#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include <string>
#include "../include/gps_data.h"
#include "../include/DataContainers/gps_position.h"
#include "../include/logger.h"
#include "../include/io.h"

Logger::Logger(std::string path) {
  entries_ = 0;
  file_path_ = path;
  remove(path.c_str());
}

void Logger::LogData(Log packet) {
  log_.latitude = packet.latitude;
  log_.longitude = packet.longitude;
  log_.timestamp = packet.timestamp;

  available_ = true;
}

void Logger::Publish() {
  if (available_) {
    //int bearing             = log_.bearing;
    double latitude = log_.latitude;
    double longitude = log_.longitude;
    //double speed            = log_.speed;
    std::string timestamp = log_.timestamp;
    //double waypoint         = log_.distance_from_waypoint;
    //double checkpoint       = log_.distance_from_destination;
    nlohmann::json j;
    j["timestamp"] = timestamp;
    j["latitude"] = latitude;
    j["longitude"] = longitude;

    IO io;
    io.WriteJsonFile(j, file_path_);
    entries_++;
    available_ = false;
  } else {
    std::cout << "NO NEW Log AVAILABLE" << std::endl;
  }
}

void Logger::PublishWaypoint(GPSData from, GPSPosition to, std::string message) {
  std::string timestamp = from.GetTime();
  double at_lat = from.GetLatitude();
  double at_lon = from.GetLongitude();

  double dest_lat = to.latitude;
  double dest_lon = to.longitude;

  nlohmann::json j;
  j["time"] = timestamp;
  j["at_lat"] = at_lat;
  j["at_lon"] = at_lon;
  j["dest_lat"] = dest_lat;
  j["dest_lon"] = dest_lon;
  j["message"] = message;

  IO io;
  io.WriteJsonFile(j, file_path_);
  entries_++;
  available_ = false;
}

