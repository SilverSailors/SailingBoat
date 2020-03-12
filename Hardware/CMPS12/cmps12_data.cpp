#include "cmps12_data.hpp"
#include <iostream>

CMPS12Data::CMPS12Data() {
  data_reading_valid_ = false;
}

void CMPS12Data::SetEntry(CMPS12DataSetRegistry entry, int data) {
  switch (entry) {
    case DATA_SET_CALIBRATION_STATE_8:calibration_ = data;
      break;
    case DATA_SET_COMPASS_BEARING_DEGREES_16:compass_bearing_degrees_ = data;
      break;
    case DATA_SET_PITCH_ANGLE_8:pitch_angle_ = data;
      break;
    case DATA_SET_ROLL_ANGLE_8:roll_angle_ = data;
      break;
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      break;
  }
}

int CMPS12Data::GetEntry(CMPS12DataSetRegistry entry) {
  switch (entry) {
    case DATA_SET_CALIBRATION_STATE_8:return calibration_;
      break;
    case DATA_SET_COMPASS_BEARING_DEGREES_16:return compass_bearing_degrees_;
      break;
    case DATA_SET_PITCH_ANGLE_8:return pitch_angle_;
      break;
    case DATA_SET_ROLL_ANGLE_8:return roll_angle_;
      break;
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      return -1;
      break;
  }
}

int CMPS12Data::GetEntry(int entry) {
  switch (entry) {
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      return -1;
      break;
  }
}

void CMPS12Data::SetEntry(int entry, int data) {
  switch (entry) {
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      break;
  }
}

void CMPS12Data::SetValid(bool valid) {
  data_reading_valid_ = valid;
}

bool CMPS12Data::GetValid() {
  return data_reading_valid_;
}
