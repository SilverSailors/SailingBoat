#ifndef SAILINGBOAT_INCLUDE_CMPS12_DATA_H_
#define SAILINGBOAT_INCLUDE_CMPS12_DATA_H_
#include <inttypes.h>
#include <vector>
#include "cmps12_data_registry.h"

class CMPS12Data {
 public:
  CMPS12Data();
  void SetEntry(CMPS12DataSetRegistry entry, int data);
  void SetEntry(int entry, int data);
  int GetEntry(CMPS12DataSetRegistry entry);
  int GetEntry(int entry);
  void SetValid(bool valid);
  bool GetValid();
 private:
  bool data_reading_valid_;
  int command_register_;
  int compass_bearing_8bit_;
  //int   compass_bearing_16bit_;
  int pitch_angle_;
  int roll_angle_;
  //int   magnometer_x_axis_;
  //int   magnometer_y_axis_;
  //int   magnometer_z_axis_;
  //int   accelerometer_x_axis_;
  //int   accelerometer_y_axis_;
  //int   accelerometer_z_axis_;
  //int   gyro_x_axis_;
  //int   gyro_y_axis_;
  //int   gyro_z_axis_;
  //int   temperature_;
  int compass_bearing_degrees_;
  //int   pitch_angle_16bit_;
  int calibration_;
};

#endif // SAILINGBOAT_INCLUDE_CMPS12_DATA_H_
