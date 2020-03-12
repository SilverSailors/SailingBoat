#include <iostream>
#include "module_cmps12.hpp"
#include "../../Core/Io/io.hpp"
#include "../../Core/Parser/parser.hpp"
#include "../../Utilities/utilities.hpp"

ModuleCmps12::ModuleCmps12() {
  std::cout << "Constructing [Module] : Cmps12" << std::endl;
  initialized_ = false;
  new_data_available_ = false;
}

ModuleCmps12::~ModuleCmps12() {

}

bool ModuleCmps12::Init() {
  std::cout << "Module Initializing" << std::endl;

  bool state = CMPS12_hardware_connection_.Init();
  initialized_ = state;

  Io io;
  Parser parser;
  std::vector<std::string> data_raw = io.ReadFile("Settings/sensor_config.txt");
  std::vector<std::string> data_clean = parser.RemoveComments(data_raw);
  internal_offset_ = std::atof(data_clean[0].c_str());
  std::cout << "Internal Offset (COMPASS): " << internal_offset_ << std::endl;
  return state;
}

void ModuleCmps12::Run() {
  if (initialized_) {
    Cmps12Data data;
    data = CMPS12_hardware_connection_.Read();
    if (data.GetValid()) {
      CMPS12_data_reading_ = data;
      new_data_available_ = true;
      int bearing = CMPS12_data_reading_.GetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16);
      int calibrated = Utilities::Normalize(bearing + internal_offset_);
      CMPS12_data_reading_.SetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16, calibrated);
    } else {
      std::cout << "CONNECTION ERROR: CHECK CABLING" << std::endl;
    }
  }
}

bool ModuleCmps12::GetInitialized() {
  return initialized_;
}

Cmps12Data ModuleCmps12::GetReading() {
  return CMPS12_data_reading_;
}

void ModuleCmps12::Report() {
  if (new_data_available_) {
    std::cout << "- - COMPASS SENSOR - -" << std::endl;
    std::cout << "Bearing: " << CMPS12_data_reading_.GetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16) << std::endl;
    std::cout << "Pitch  : " << CMPS12_data_reading_.GetEntry(DATA_SET_PITCH_ANGLE_8) << std::endl;
    std::cout << "Roll   : " << CMPS12_data_reading_.GetEntry(DATA_SET_ROLL_ANGLE_8) << std::endl;
    std::cout << "----------------------" << std::endl;
    new_data_available_ = false;
  }
}

bool ModuleCmps12::IsNewDataAvilable() {
  return new_data_available_;
}
