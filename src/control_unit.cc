#include "../include/control_unit.h"
#include "../include/io.h"
#define CALCULATED_THRESHOLD 5.0 / 2.0;

ControlUnit::ControlUnit(std::string destination) {
  active_ = false;

  IO io;
  std::vector<std::string> data = io.ReadFile(destination);

  for (size_t i = 0; i < data.size(); i+=2) {
    GPSData gps_data;
    gps_data.latitude = std::atof(data[i].c_str());
    gps_data.longitude = std::atof(data[i+1].c_str());
    destination_.push(gps_data);
  }
  active_ = true;
}

bool ControlUnit::IsActive() {
  return active_;
}

GPSData ControlUnit::GetDestination() {
  return destination_.front();
}

void ControlUnit::UpdateJourney() {
  if (destination_.size() > 0) {
    destination_.pop();
  } else {
    active_ = false;
  }
}

double ControlUnit::GetCalculatedThreshold() {
  return CALCULATED_THRESHOLD;
}
