#include "module_gps.hpp"
#include <iostream>

ModuleGps::ModuleGps() {
  std::cout << "Constructing [Module] Gps Module" << std::endl;
  initialized_ = false;
  new_data_available_ = false;
}

bool ModuleGps::Init() {
  bool result = gps_hardware_connection_.Init();
  initialized_ = result;
  return result;
}

void ModuleGps::Run() {
  if (initialized_) {
    GpsData reading = gps_hardware_connection_.Read();
    if (reading.GetValid()) {
      data_reading_ = reading;
      new_data_available_ = true;
    } else {
      std::cout << "Gps: DATA READING NOT VALID" << std::endl;
    }
  }
}

GpsData ModuleGps::GetReading() {
  return data_reading_;
}

void ModuleGps::Report() {
  if (new_data_available_) {
    std::cout << "- - Gps SENSOR - -" << std::endl;
    std::cout << "Gps LAT : " << data_reading_.GetLatitude() << std::endl;
    std::cout << "Gps LON : " << data_reading_.GetLongitude() << std::endl;
    std::cout << "Gps TIME: " << data_reading_.GetTime() << std::endl;
    std::cout << "Gps TIME: " << data_reading_.GetTimeValue() << std::endl;
    std::cout << "------------------" << std::endl;
    new_data_available_ = false;
  }
}

bool ModuleGps::IsNewDataAvilable() {
  return new_data_available_;
}
