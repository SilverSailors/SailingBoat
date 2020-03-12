#include "module_gps.hpp"
#include <iostream>

ModuleGPS::ModuleGPS() {
  std::cout << "Constructing [Module] GPS Module" << std::endl;
  initialized_ = false;
  new_data_available_ = false;
}

bool ModuleGPS::Init() {
  bool result = gps_hardware_connection_.Init();
  initialized_ = result;
  return result;
}

void ModuleGPS::Run() {
  if (initialized_) {
    GPSData reading = gps_hardware_connection_.Read();
    if (reading.GetValid()) {
      data_reading_ = reading;
      new_data_available_ = true;
    } else {
      std::cout << "GPS: DATA READING NOT VALID" << std::endl;
    }
  }
}

GPSData ModuleGPS::GetReading() {
  return data_reading_;
}

void ModuleGPS::Report() {
  if (new_data_available_) {
    std::cout << "- - GPS SENSOR - -" << std::endl;
    std::cout << "GPS LAT : " << data_reading_.GetLatitude() << std::endl;
    std::cout << "GPS LON : " << data_reading_.GetLongitude() << std::endl;
    std::cout << "GPS TIME: " << data_reading_.GetTime() << std::endl;
    std::cout << "GPS TIME: " << data_reading_.GetTimeValue() << std::endl;
    std::cout << "------------------" << std::endl;
    new_data_available_ = false;
  }
}

bool ModuleGPS::IsNewDataAvilable() {
  return new_data_available_;
}
