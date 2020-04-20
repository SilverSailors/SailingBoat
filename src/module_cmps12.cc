#include <iostream>
#include "../include/module_cmps12.h"
#include "../include/calculation_unit.h"

ModuleCMPS12::ModuleCMPS12() {
  initialized_ = CMPS12_hardware_connection_.GetInitialized();
  data_reading_ = 0;
}

bool ModuleCMPS12::GetInitialized() {
  return initialized_;
}

void ModuleCMPS12::Run() {
  if (initialized_) {
    int data = CMPS12_hardware_connection_.Read();
    if (data != -1) {
      // Only overwrites on valid compass calibration
      data_reading_ = CalculationUnit::NormalizeDegrees(data);
    }
  }
}

int ModuleCMPS12::GetReading() {
  return data_reading_;
}

void ModuleCMPS12::Report() {
  std::cout << "Boat heading            : " << data_reading_ << std::endl;
}
