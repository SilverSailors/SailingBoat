#include "CMPS12_data.hpp"
#include <iostream>

CMPS12_DATA::CMPS12_DATA() {
  m_data_reading_valid = false;
}

void CMPS12_DATA::set_entry(DATA_SET_REGISTRY entry, int data) {
  switch (entry) {
    case DATA_SET_CALIBRATION_STATE_8:m_calibration = data;
      break;

    case DATA_SET_COMPASS_BEARING_DEGREES_16:m_compass_bearing_degrees = data;
      break;

    case DATA_SET_PITCH_ANGLE_8:m_pitch_angle = data;
      break;

    case DATA_SET_ROLL_ANGLE_8:m_roll_angle = data;
      break;

    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      break;
  }
}

int CMPS12_DATA::get_entry(DATA_SET_REGISTRY entry) {
  switch (entry) {
    case DATA_SET_CALIBRATION_STATE_8:return m_calibration;
      break;

    case DATA_SET_COMPASS_BEARING_DEGREES_16:return m_compass_bearing_degrees;
      break;

    case DATA_SET_PITCH_ANGLE_8:return m_pitch_angle;
      break;

    case DATA_SET_ROLL_ANGLE_8:return m_roll_angle;
      break;

    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      return -1;
      break;
  }
}

int CMPS12_DATA::get_entry(int entry) {
  switch (entry) {
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      return -1;
      break;

  }
}

void CMPS12_DATA::set_entry(int entry, int data) {
  switch (entry) {
    default:std::cout << "NOT IMPLEMENTED IN THIS VERSION" << std::endl;
      break;

  }
}

void CMPS12_DATA::set_valid(bool valid) {
  m_data_reading_valid = valid;
}

bool CMPS12_DATA::get_valid() {
  return m_data_reading_valid;
}
