#include "logger.h"
#include <string>
#include "../IO/io.h"
#include "../../Hardware/GPS/gps_data.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Logger::Logger(std::string path) {
  entries_ = 0;
  file_path_ = path;
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

    std::stringstream stream;
    stream << timestamp << " " << std::setprecision(15) << latitude << " " << std::setprecision(15) << longitude;

    std::string output = stream.str();

    IO io;
    io.WriteFile(output, file_path_);
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

  std::stringstream stream;
  stream << timestamp
         << " : "
         << std::setprecision(10) << at_lat
         << " "
         << std::setprecision(10) << at_lon
         << " (->) "
         << std::setprecision(10) << dest_lat
         << " "
         << std::setprecision(10) << dest_lon;
  std::string output = stream.str();

  IO io;
  io.WriteFile(output + " : " + message, file_path_);
  entries_++;
  available_ = false;
}

void Logger::Write(std::string message) {
  std::stringstream stream;
  stream << message;

  IO io;
  io.WriteFile(message, file_path_);
}
