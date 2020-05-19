#include "../include/control_unit.h"
#include "../include/io.h"

ControlUnit::ControlUnit(const std::string &destinations) {
  active_ = false;

  std::vector<std::string> data = IO::ReadFile(destinations);

  if (data.size() % 2 == 0) {
    // Loops through all rows from file, one row per coordinate
    for (size_t i = 0; i < data.size(); i += 2) {
      GPSData gps_data;
      gps_data.latitude = std::strtod(data[i].c_str(), nullptr);
      gps_data.longitude = std::strtod(data[i + 1].c_str(), nullptr);
      destinations_.push(gps_data);
    }
    if (destinations_.size() >= 2) {
      active_ = true;
    }
  }
}

bool ControlUnit::IsActive() {
  return active_;
}

GPSData ControlUnit::GetDestination() {
  if (destinations_.empty()) return {};
  else return destinations_.front();
}

void ControlUnit::UpdateJourney() {
  // Sets active false on last destination reached
  if (!destinations_.empty()) {
    destinations_.pop();
    if (destinations_.empty()) {
      active_ = false;
    }
  }
}
