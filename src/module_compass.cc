#include <iostream>
#include "../include/module_compass.h"
#include "../include/calculation_unit.h"

ModuleCompass::ModuleCompass() {
  data_reading_ = -1;
  initialized_ = CMPS12_hardware_connection_.GetInitialized();
}

bool ModuleCompass::GetInitialized() {
  return initialized_;
}

void ModuleCompass::Run() {
  if (initialized_) {
    int data = CMPS12_hardware_connection_.Read();
    if (data != -1) {
      // Only overwrites on valid compass calibration
      data_reading_ = CalculationUnit::NormalizeDegrees(data);
    }
  }
}

int ModuleCompass::GetReading() {
  return data_reading_;
}

void ModuleCompass::Report() {
  std::cout << "Boat heading            : " << data_reading_ << std::endl;
}
