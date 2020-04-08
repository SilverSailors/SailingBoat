#include <cstdio>
#include <string>
#include "../include/logger.h"
#include "../include/io.h"

Logger::Logger(std::string path) {
  file_path_ = path;
  remove(path.c_str());
}

void Logger::LogData(Log packet) {
  log_.entry_id = packet.entry_id;
  log_.latitude = packet.latitude;
  log_.longitude = packet.longitude;
  log_.timestamp = packet.timestamp;
  available_ = true;
}

void Logger::Publish() {
  if (available_) {
    nlohmann::json json_obj;
    json_obj["entry_id"] = log_.entry_id;
    json_obj["latitude"] = log_.latitude;
    json_obj["longitude"] = log_.longitude;
    json_obj["timestamp"] = log_.timestamp;

    IO io;
    io.WriteFile(json_obj, file_path_);
    available_ = false;
  }
}

void Logger::PublishWaypoint(GPSData from, GPSData to, std::string message) {
  nlohmann::json json_obj;
  json_obj["at_lat"] = from.latitude;
  json_obj["at_lon"] = from.latitude;
  json_obj["dest_lat"] = to.latitude;
  json_obj["dest_lon"] = to.longitude;
  json_obj["message"] = message;
  json_obj["time"] = from.timestamp;

  IO io;
  io.WriteFile(json_obj, file_path_);
  available_ = false;
}
