#include <string>
#include "../include/logger.h"
#include "../include/io.h"

Logger::Logger(std::string path) {
  file_path_ = path;
}

void Logger::LogData(Log packet) {
  log_.entry_id = packet.entry_id;
  log_.latitude = packet.latitude;
  log_.longitude = packet.longitude;
  log_.wind_angle = packet.wind_angle;
  log_.boat_heading = packet.boat_heading;
  log_.destination_latitude = packet.destination_latitude;
  log_.destination_longitude = packet.destination_longitude;
  log_.destination_distance = packet.destination_distance;
  log_.route_angle = packet.route_angle;
  log_.rudder_angle = packet.rudder_angle;
  log_.sail_angle = packet.sail_angle;
  log_.timestamp = packet.timestamp;
  available_ = true;
}

void Logger::Publish() {
  // Only when new log is received
  if (available_) {
    nlohmann::json json_obj;
    json_obj["entry_id"] = log_.entry_id;
    json_obj["latitude"] = log_.latitude;
    json_obj["longitude"] = log_.longitude;
    json_obj["wind_angle"] = log_.wind_angle;
    json_obj["boat_heading"] = log_.boat_heading;
    json_obj["destination_latitude"] = log_.destination_latitude;
    json_obj["destination_longitude"] = log_.destination_longitude;
    json_obj["destination_distance"] = log_.destination_distance;
    json_obj["route_angle"] = log_.route_angle;
    json_obj["rudder_angle"] = log_.rudder_angle;
    json_obj["sail_angle"] = log_.sail_angle;
    json_obj["timestamp"] = log_.timestamp;

    IO io;
    io.WriteFile(json_obj, file_path_);
    available_ = false;
  }
}

void Logger::PublishWaypoint(GPSData from, GPSData to, std::string message) {
  nlohmann::json json_obj;
  json_obj["at_lat"] = from.latitude;
  json_obj["at_long"] = from.longitude;
  json_obj["dest_lat"] = to.latitude;
  json_obj["dest_long"] = to.longitude;
  json_obj["message"] = message;
  json_obj["time"] = from.timestamp;

  IO io;
  io.WriteFile(json_obj, file_path_);
}
