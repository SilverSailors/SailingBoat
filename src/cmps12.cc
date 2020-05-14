#include "../include/cmps12.h"
#include <iostream>
#include <vector>
#include <wiringPi.h>
#include <wiringPiI2C.h>
constexpr int I2C_DEVICE_ADDRESS = 0x60;
constexpr int TOTAL_REGISTRY_ENTRIES = 31;
constexpr int COMPASS_BEARING_16_HIGH_BYTE_DEGREES = 0x1A;
constexpr int COMPASS_BEARING_16_LOW_BYTE_DEGREES = 0x1B;
constexpr int CALIBRATION_STATE_8 = 0x1E;

CMPS12::CMPS12() {
  // Initializes wiringPi
  wiringPiSetup();
  // Open the I2C device, and registers the target device
  file_descriptor_ = wiringPiI2CSetup(I2C_DEVICE_ADDRESS);
  initialized_ = file_descriptor_ != -1;
}

bool CMPS12::GetInitialized() {
  return initialized_;
}

unsigned int CMPS12::Bitshift(unsigned int high, unsigned int low) {
  return high << 8u | low;
}

int CMPS12::Read() {
  std::vector<int> raw_data;
  // Reserves slots for our raw data
  raw_data.reserve(TOTAL_REGISTRY_ENTRIES);

  // Reads values from the device registered
  for (int i = 0; i < TOTAL_REGISTRY_ENTRIES; i++) {
    raw_data[i] = wiringPiI2CReadReg8(file_descriptor_, i);
  }

  // Checks if calibration was valid (If yes then usually the data was OK)
  if (raw_data[CALIBRATION_STATE_8] == -1) {
    return -1;
  }

  // Bitshifts raw compass bearing
  return (int)Bitshift(raw_data[COMPASS_BEARING_16_HIGH_BYTE_DEGREES],
                  raw_data[COMPASS_BEARING_16_LOW_BYTE_DEGREES]) / 16;
}
