#ifndef SAILINGBOAT_HARDWARE_CMPS12_CMPS12_H_
#define SAILINGBOAT_HARDWARE_CMPS12_CMPS12_H_
#include "cmps12_data.h"

class CMPS12 {
 public:
  CMPS12();
  //Establish connection to I2C device
  bool Init();
  //Read data from I2C Pins, return retrieved data
  CMPS12Data Read();
 private:
  int Bitshift(int high, int low);
  const int total_registry_entries_ = 31;
  const int i2c_device_address_ = 0x60;
  const char *i2c_device_path_ = "/dev/i2c-1";
  bool initialized_;
  int file_descriptor_;
};

#endif // SAILINGBOAT_HARDWARE_CMPS12_CMPS12_H_
