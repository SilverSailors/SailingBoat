#ifndef SAILINGBOAT_INCLUDE_CMPS12_H_
#define SAILINGBOAT_INCLUDE_CMPS12_H_
#include "cmps12_data.h"

class CMPS12 {
 public:
  /**
   * The constructor, initializes member fields
   */
  CMPS12();
  /**
   * Initializes CMPS12 hardware connection
   * @return boolean value on successful initialization
   */
  bool Init();
  /**
   * Reads data from CMPS12 component
   * @return Retrieved compass data
   */
  CMPS12Data Read();
 private:
  /**
    * Shifts bits with a left shift
    * @param high Bits to be shifted
    * @param low Endian value
    * @return Result from shift
    */
  int Bitshift(int high, int low);
  /**
   * Total registry entries, when reading from CMPS12 component
   */
  const int total_registry_entries_ = 31;
  /**
   * I2C device address, when initializing CMPS12 component
   */
  const int i2c_device_address_ = 0x60;
  /**
   * Not in use
   */
  const char *i2c_device_path_ = "/dev/i2c-1";
  /**
   * Initialized, boolean value on CMPS12 component initialized or not
   */
  bool initialized_;
  /**
   * File descriptor, connection to hardware
   */
  int file_descriptor_;
};

#endif // SAILINGBOAT_INCLUDE_CMPS12_H_
