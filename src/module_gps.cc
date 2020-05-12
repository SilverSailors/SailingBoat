#include "../include/module_gps.h"
#include <iostream>

ModuleGPS::ModuleGPS() {
  data_reading_ = {};
  initialized_ = gps_hardware_connection_.GetInitialized();
}

bool ModuleGPS::GetInitialized() {
  return initialized_;
}

void ModuleGPS::Run() {
  if(initialized_) {
    GPSData gps_data = gps_hardware_connection_.Read();
    if(!gps_data.timestamp.empty()) {
      data_reading_ = gps_data;
      data_readings_.push_back(gps_data);
    }
  }
}

GPSData ModuleGPS::GetReading() {
  return data_reading_;
}

GPSData ModuleGPS::GetMeanReading() {
  if(data_readings_.size() > 10) {
    data_readings_.pop_front();
  }

  GPSData mean = { };
  for(std::size_t i = 0; i < data_readings_.size(); i++) {
    mean.longitude += data_readings_[i].longitude;
    mean.latitude += data_readings_[i].latitude;
  }

  mean.longitude /= data_readings_.size();
  mean.latitude /= data_readings_.size();
  mean.timestamp = data_reading_.timestamp;

  return mean;
}

void ModuleGPS::Report() {
  std::cout << "Boat position lat       : " << data_reading_.latitude << std::endl;
  std::cout << "Boat position long      : " << data_reading_.longitude << std::endl;
  std::cout << "Timestamp               : " << data_reading_.timestamp << std::endl;
}
