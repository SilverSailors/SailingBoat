#include "../include/module_wind_sensor.h"
#include "../include/utilities.h"
#include "../include/io.h"
#include "../include/parser.h"
#include <iostream>
#include <vector>

ModuleWindSensor::ModuleWindSensor(int spi_channel) {
  std::cout << "Constructing [Module] Wind Sensor" << std::endl;
  initialized_ = false;
  new_data_available_ = false;
  spi_channel_ = spi_channel;
  internal_offset_ = 0;
}

bool ModuleWindSensor::Init() {
  //bool result = hardware_connection_ma3_.Init(spi_channel_);
  bool result = true;

  initialized_ = result;

  IO io;
  Parser parser;
  std::vector<std::string> data_raw = io.ReadFile("/home/alarm/.config/sailingBoat/settings/sensor_config.txt");
  std::vector<std::string> data_clean = parser.RemoveComments(data_raw);
  internal_offset_ = std::atof(data_clean[2].c_str());
  std::cout << "Internal Offset (WIND SENSOR): " << internal_offset_ << std::endl;
  return result;
}

void ModuleWindSensor::Run() {
  //The values retrieved from the sensor need to be converted to our range
  //(Initial values are between 2-1020, we want 0 - 359

  // old code
  //int reading = hardware_connection_ma3_.Read(spi_channel_);

  int reading = 100;

  int bearing_uncorrected = Utilities::ConvertCoordinates(2, 1020, 0, 359, reading);
  reading_ = Utilities::Normalize(bearing_uncorrected + internal_offset_);
  new_data_available_ = true;
}

int ModuleWindSensor::GetReading() {
  return reading_;
}

void ModuleWindSensor::Report() {
  if (new_data_available_) {
    std::cout << "- - WIND SENSOR - -" << std::endl;
    std::cout << "Wind Bearing: " << reading_ << std::endl;
    std::cout << "-------------------" << std::endl;
    new_data_available_ = false;
  }
}

bool ModuleWindSensor::IsNewDataAvailable() {
  return new_data_available_;
}
