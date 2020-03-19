#ifndef SAILINGBOAT_INCLUDE_CMPS12_DATA_REGISTRY_H_
#define SAILINGBOAT_INCLUDE_CMPS12_DATA_REGISTRY_H_

/**
 * CMPS12 Data set registry
 */
typedef enum {
  /**
   * Not in use
   */
  DATA_SET_COMMAND_REGISTER_SOFTWARE_READ_8 = 0x00,
  /**
   * Not in use
   */
  DATA_SET_COMPASS_BEARING_8 = 0x01,
  /**
   * Not in use
   */
  DATA_SET_COMPASS_BEARING_16 = 0x02,
  /**
   * Pith angle 8bit, registry used by CMPS12
   */
  DATA_SET_PITCH_ANGLE_8 = 0x03,
  /**
   * Roll angle 8bit, registry used by CMPS12
   */
  DATA_SET_ROLL_ANGLE_8 = 0x04,
  /**
   * Not in use
   */
  DATA_SET_MAGNETOMETER_X_RAW_16 = 0x05,
  /**
   * Not in use
   */
  DATA_SET_MAGNETOMETER_Y_RAW_16 = 0x06,
  /**
   * Not in use
   */
  DATA_SET_MAGNETOMETER_Z_RAW_16 = 0x07,
  /**
   * Not in use
   */
  DATA_SET_ACCELEROMETER_X_RAW_16 = 0x08,
  /**
   * Not in use
   */
  DATA_SET_ACCELEROMETER_Y_RAW_16 = 0x09,
  /**
   * Not in use
   */
  DATA_SET_ACCELEROMETER_Z_RAW_16 = 0x0A,
  /**
   * Not in use
   */
  DATA_SET_GYRO_X_RAW_16 = 0x0B,
  /**
   * Not in use
   */
  DATA_SET_GYRO_Y_RAW_16 = 0x0C,
  /**
   * Not in use
   */
  DATA_SET_GYRO_Z_RAW_16 = 0x0D,
  /**
   * Not in use
   */
  DATA_SET_COMPASS_TEMPERATURE_16 = 0x0E,
  /**
   * Compass bearing degrees 16bit, registry used by CMPS12
   */
  DATA_SET_COMPASS_BEARING_DEGREES_16 = 0x0F,
  /**
   * Not in use
   */
  DATA_SET_PITCH_ANGLE_16 = 0x10,
  /**
   * Calibration state 8bit, registry used by CMPS12
   */
  DATA_SET_CALIBRATION_STATE_8 = 0x11
} CMPS12DataSetRegistry;

#endif // SAILINGBOAT_INCLUDE_CMPS12_DATA_REGISTRY_H_
