#ifndef __CMPS12_HPP__
#define __CMPS12_HPP__
#include "CMPS12_data.hpp"

class CMPS12 {
 public:
  CMPS12();
  //Establish connection to I2C device
  bool init();
  //Read data from I2C Pins, return retrieved data
  CMPS12_DATA read();

 private:
  int bitshift(int high, int low);
  const int TOTAL_REGISTRY_ENTRIES = 31;
  const int I2C_DEVICE_ADDRESS = 0x60;
  const char *I2C_DEVICE_PATH = "/dev/i2c-1";
  bool m_initialized;
  int m_file_descriptor;
};

#endif //__CMPS12_HPP__
