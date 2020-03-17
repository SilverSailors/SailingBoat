#include "../include/cmps12.h"
#include <iostream>
#include <vector>
#include "../include/cmps12_i2c_registry.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

CMPS12::CMPS12() {
  file_descriptor_ = 0;
  initialized_ = false;
}

int CMPS12::Bitshift(int high, int low) {
  int result = (high << 8 | low);
  return result;
}

bool CMPS12::Init() {
  std::cout << "CMPS Hardware Initializing" << std::endl;
  wiringPiSetup();
  file_descriptor_ = wiringPiI2CSetup(i2c_device_address_);
  if (file_descriptor_ == -1) {
    std::cout << "CMPS Hardware Failed to Initialize" << std::endl;
    initialized_ = false;
  }
  initialized_ = true;
  return initialized_;
}

CMPS12Data CMPS12::Read() {
  CMPS12Data compass_data;

  ///
  ///Read data if we are initialized
  ///
  if (initialized_) {
    std::vector<int> raw_data;
    ///
    ///Reserve 31 Slots for our raw data
    ///
    raw_data.reserve(31);

    for (int i = 0; i < total_registry_entries_; i++) {
      raw_data[i] = wiringPiI2CReadReg8(file_descriptor_, i);
    }

    ///
    ///Check if calibration was valid (If yes then usually the data was OK Read)
    ///
    if (raw_data[CALIBRATION_STATE_8] == -1) {
      compass_data.SetValid(false);
      return compass_data;
    }

    ///
    ///Data set is valid
    ///
    compass_data.SetValid(true);

    ///
    ///Bitshift relevant required data
    ///
    int bearing_16 = Bitshift(
        raw_data[COMPASS_BEARING_16_HIGH_BYTE_DEGREES], raw_data[COMPASS_BEARING_16_LOW_BYTE_DEGREES]) / 16;

    //data_set.SetEntry()
    compass_data.SetEntry(DATA_SET_CALIBRATION_STATE_8, raw_data[CALIBRATION_STATE_8]);
    compass_data.SetEntry(DATA_SET_ROLL_ANGLE_8, raw_data[ROLL_ANGLE_8]);
    compass_data.SetEntry(DATA_SET_PITCH_ANGLE_8, raw_data[PITCH_ANGLE_8]);
    compass_data.SetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16, bearing_16);

    return compass_data;
  } else {
    std::cout << "CMPS Hardware Not Initialized" << std::endl;
    return compass_data;
  }
}
