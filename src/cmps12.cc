#include "../include/cmps12.h"
#include <iostream>
#include <vector>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define I2C_DEVICE_ADDRESS 0x60
#define TOTAL_REGISTRY_ENTRIES 31
#define COMPASS_BEARING_16_HIGH_BYTE_DEGREES 0x1A
#define COMPASS_BEARING_16_LOW_BYTE_DEGREES 0x1B
#define CALIBRATION_STATE_8 0x1E

CMPS12::CMPS12() {
  std::cout << "Constructing [Hardware] CMPS12" << std::endl;
  wiringPiSetup();
  file_descriptor_ = wiringPiI2CSetup(I2C_DEVICE_ADDRESS);
  initialized_ = file_descriptor_ != -1;
}

bool CMPS12::GetInitialized() {
  return initialized_;
}

int CMPS12::Bitshift(int high, int low) {
  int result = (high << 8 | low);
  return result;
}

int CMPS12::Read() {
  std::vector<int> raw_data;
  // Reserve 31 Slots for our raw data
  raw_data.reserve(TOTAL_REGISTRY_ENTRIES);

  for (int i = 0; i < TOTAL_REGISTRY_ENTRIES; i++) {
    raw_data[i] = wiringPiI2CReadReg8(file_descriptor_, i);
  }

  // Check if calibration was valid (If yes then usually the data was OK Read)
  if (raw_data[CALIBRATION_STATE_8] == -1) {
    return -1;
  }

  // Bitshift compass bearing
  return Bitshift(raw_data[COMPASS_BEARING_16_HIGH_BYTE_DEGREES], 
                  raw_data[COMPASS_BEARING_16_LOW_BYTE_DEGREES]) / 16;
}
