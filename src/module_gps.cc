#include "../include/module_gps.h"
#include <iostream>
constexpr int READINGS_TO_CONSIDER = 5;

ModuleGPS::ModuleGPS() {
  data_reading_ = {};
  initialized_ = gps_hardware_connection_.GetInitialized();
}

bool ModuleGPS::GetInitialized() {
  return initialized_;
}

void ModuleGPS::Run() {
  if (initialized_) {
    GPSData gps_data = gps_hardware_connection_.Read();
    if (!gps_data.timestamp.empty()) {
      if (data_readings_.size() < READINGS_TO_CONSIDER) {
        data_readings_.push_front(gps_data);
      } else {
        data_readings_.push_front(gps_data);
        data_readings_.pop_back();
      }
    }
    GPSData tmp_gps_data = {};
    for (const GPSData &data_reading : data_readings_) {
      tmp_gps_data = tmp_gps_data + data_reading;
    }
    data_reading_ = gps_data / data_readings_.size();
  }
}

GPSData ModuleGPS::GetReading() {
  return data_reading_;
}

void ModuleGPS::Report() {
  std::cout << "Boat position lat       : " << data_reading_.latitude << std::endl;
  std::cout << "Boat position long      : " << data_reading_.longitude << std::endl;
  std::cout << "Timestamp               : " << data_reading_.timestamp << std::endl;
}
