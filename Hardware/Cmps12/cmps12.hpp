#ifndef __CMPS12_HPP__
#define __CMPS12_HPP__
#include "cmps12_data.hpp"

class Cmps12 {
 public:
  Cmps12();
  //Establish connection to I2C device
  bool Init();
  //Read data from I2C Pins, return retrieved data
  Cmps12Data Read();
 private:
  int Bitshift(int high, int low);
  const int total_registry_entries_ = 31;
  const int i2c_device_address_ = 0x60;
  const char *i2c_device_path_ = "/dev/i2c-1";
  bool initialized_;
  int file_descriptor_;
};

#endif //__CMPS12_HPP__
