#include <iostream>
#include "../include/module_cmps12.h"
#include "../include/calculation_unit.h"

ModuleCMPS12::ModuleCMPS12() {
  new_data_available_ = false;
  initialized_ = CMPS12_hardware_connection_.GetInitialized();
}

bool ModuleCMPS12::GetInitialized() {
  return initialized_;
}

void ModuleCMPS12::Run() {
  if (initialized_) {
    int data = CMPS12_hardware_connection_.Read();
    if (data != -1) {
      new_data_available_ = true;
      data_reading_ = CalculationUnit::NormalizeDegrees(data);
    }
  }
}

int ModuleCMPS12::GetReading() {
  return data_reading_;
}

void ModuleCMPS12::Report() {
  if (new_data_available_) {
    std::cout << "- - COMPASS SENSOR - -" << std::endl;
    std::cout << "Bearing: " << data_reading_ << std::endl;
    std::cout << "------------------" << std::endl;
    new_data_available_ = false;
  }
}
