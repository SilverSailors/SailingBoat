#ifndef SAILINGBOAT_INCLUDE_CMPS12_DATA_H_
#define SAILINGBOAT_INCLUDE_CMPS12_DATA_H_
#include <inttypes.h>
#include <vector>
#include "cmps12_data_registry.h"

class CMPS12Data {
 public:
  /**
   * The constructor, initializes member fields
   */
  CMPS12Data();
  /**
   * Sets from entry, corresponding member field value to data
   * @param entry CMPS12DataSetRegistry entry
   * @param data Data to set
   */
  void SetEntry(CMPS12DataSetRegistry entry, int data);
  /**
   * Not in use
   * @param entry
   * @param data
   */
  void SetEntry(int entry, int data);
  /**
   * Returns based on entry, corresponding member field value
   * @param entry CMPS12DataSetRegistry entry
   * @return Member field value
   */
  int GetEntry(CMPS12DataSetRegistry entry);
  /**
   * Not in use
   * @param entry
   * @return Entry
   */
  int GetEntry(int entry);
  /**
   * Updated "data_reading_valid_" member field with boolean value
   * @param valid Boolean value
   */
  void SetValid(bool valid);
  /**
   * Returns "data_reading_valid_" member field value
   * @return "data_reading_valid_" boolean value
   */
  bool GetValid();
 private:
  /**
   * Data reading valid, If data reading is valid
   */
  bool data_reading_valid_;
  /**
   * Not in use
   */
  int command_register_;
  /**
   * Not in use
   */
  int compass_bearing_8bit_;
  /**
   * Not in use
   */
  //int compass_bearing_16bit_;
  /**
   * Pitch angle, corresponding CMPS12DataSetRegistry entry
   */
  int pitch_angle_;
  /**
   * Roll angle, corresponding CMPS12DataSetRegistry entry
   */
  int roll_angle_;
  /**
   * Not in use
   */
  //int magnometer_x_axis_;
  /**
   * Not in use
   */
  //int magnometer_y_axis_;
  /**
   * Not in use
   */
  //int magnometer_z_axis_;
  /**
   * Not in use
   */
  //int accelerometer_x_axis_;
  /**
   * Not in use
   */
  //int accelerometer_y_axis_;
  /**
   * Not in use
   */
  //int accelerometer_z_axis_;
  /**
   * Not in use
   */
  //int gyro_x_axis_;
  /**
   * Not in use
   */
  //int gyro_y_axis_;
  /**
   * Not in use
   */
  //int gyro_z_axis_;
  /**
   * Not in use
   */
  //int temperature_;
  /**
   * Compass bearing degrees, corresponding CMPS12DataSetRegistry entry
   */
  int compass_bearing_degrees_;
  /**
   * Not in use
   */
  //int pitch_angle_16bit_;
  /**
   * Calibration, corresponding CMPS12DataSetRegistry entry
   */
  int calibration_;
};

#endif // SAILINGBOAT_INCLUDE_CMPS12_DATA_H_
