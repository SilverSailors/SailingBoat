#include "../include/control_unit.h"
#include "../include/io.h"

ControlUnit::ControlUnit(std::string destination) {
  active_ = false;

  IO io;
  std::vector<std::string> data = io.ReadFile(std::move(destination));

  // Loops through all rows from file, one row per coordinate
  for (size_t i = 0; i < data.size(); i += 2) {
    GPSData gps_data;
    gps_data.latitude = std::strtod(data[i].c_str(), nullptr);
    gps_data.longitude = std::strtod(data[i + 1].c_str(), nullptr);
    destination_.push(gps_data);
  }
  active_ = true;
}

bool ControlUnit::IsActive() {
  return active_;
}

GPSData ControlUnit::GetDestination() {
  if (destination_.empty()) return {};
  else return destination_.front();
}

void ControlUnit::UpdateJourney() {
  // Sets active false on last destination reached
  if (!destination_.empty()) {
    destination_.pop();
    if (destination_.empty()) {
      active_ = false;
    }
  }
}
