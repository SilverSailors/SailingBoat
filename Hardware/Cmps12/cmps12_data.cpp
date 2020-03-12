#include "cmps12_data.hpp"
#include <iostream>

Cmps12Data::Cmps12Data() {
  data_reading_valid_ = false;
}

void Cmps12Data::SetEntry(DataSetRegistry entry, int data) {
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

int Cmps12Data::GetEntry(DataSetRegistry entry) {
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

int Cmps12Data::GetEntry(int entry) {
  switch (entry) {
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      return -1;
      break;
  }
}

void Cmps12Data::SetEntry(int entry, int data) {
  switch (entry) {
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      break;
  }
}

void Cmps12Data::SetValid(bool valid) {
  data_reading_valid_ = valid;
}

bool Cmps12Data::GetValid() {
  return data_reading_valid_;
}
