#include "../include/module_gps.h"
#include <iostream>

ModuleGPS::ModuleGPS() {
  initialized_ = gps_hardware_connection_.GetInitialized();
}

bool ModuleGPS::GetInitialized() {
  return initialized_;
}

void ModuleGPS::Run() {
  if(initialized_) {
    GPSData gps_data = gps_hardware_connection_.Read();
    if((gps_data.latitude >= 0.0) && (gps_data.longitude >= 0.0)) {
      data_reading_ = gps_data;
    }
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
