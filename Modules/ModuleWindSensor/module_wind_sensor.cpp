#include "module_wind_sensor.hpp"
#include "../../Utilities/utilities.hpp"
#include "../../Core/Io/io.hpp"
#include "../../Core/Parser/parser.hpp"
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
  bool result = hardware_connection_ma3_.Init(spi_channel_);
  initialized_ = result;

  Io io;
  Parser parser;
  std::vector<std::string> data_raw = io.ReadFile("Settings/sensor_config.txt");
  std::vector<std::string> data_clean = parser.RemoveComments(data_raw);
  internal_offset_ = std::atof(data_clean[2].c_str());
  std::cout << "Internal Offset (WIND SENSOR): " << internal_offset_ << std::endl;
  return result;
}

void ModuleWindSensor::Run() {
  //The values retrieved from the sensor need to be converted to our range
  //(Initial values are between 2-1020, we want 0 - 359
  int reading = hardware_connection_ma3_.Read(spi_channel_);
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
