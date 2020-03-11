#ifndef __CMPS12_DATA_HPP__
#define  __CMPS12_DATA_HPP__
#include <inttypes.h>
#include <vector>
#include "CMPS12_DATA_registry.hpp"

class CMPS12_DATA {
 public:
  CMPS12_DATA();
  void set_entry(DATA_SET_REGISTRY entry, int data);
  void set_entry(int entry, int data);
  int get_entry(DATA_SET_REGISTRY entry);
  int get_entry(int entry);
  void set_valid(bool valid);
  bool get_valid();

 private:
  bool m_data_reading_valid;
  int m_command_register;
  int m_compass_bearing_8bit;
  //int   m_compass_bearing_16bit;
  int m_pitch_angle;
  int m_roll_angle;
  //int   m_magnometer_x_axis;
  //int   m_magnometer_y_axis;
  //int   m_magnometer_z_axis;
  //int   m_accelerometer_x_axis;
  //int   m_accelerometer_y_axis;
  //int   m_accelerometer_z_axis;
  //int   m_gyro_x_axis;
  //int   m_gyro_y_axis;
  //int   m_gyro_z_axis;
  //int   m_temperature;
  int m_compass_bearing_degrees;
  //int   m_pitch_angle_16bit;
  int m_calibration;
};

#endif //__CMPS12_DATA_HPP__
