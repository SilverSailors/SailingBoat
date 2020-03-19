#ifndef SAILINGBOAT_INCLUDE_CMPS12_I2C_REGISTRY_H_
#define SAILINGBOAT_INCLUDE_CMPS12_I2C_REGISTRY_H_

/**
 * CMPS12 I2C registry
 */
typedef enum {
  /**
   * Not in use
   */
  COMMAND_REGISTER_SOFTWARE_READ_8 = 0x00,
  /**
   * Not in use
   */
  COMPASS_BEARING_8 = 0x01,
  /**
   * Not in use
   */
  COMPASS_BEARING_16_HIGH_BYTE = 0x02,
  /**
   * Not in use
   */
  COMPASS_BEARING_16_LOW_BYTE = 0x03,
  /**
   * Pitch angle 8bit, used by CMPS12
   */
  PITCH_ANGLE_8 = 0x04,
  /**
   * Roll angle 8bit, used by CMPS12
   */
  ROLL_ANGLE_8 = 0x05,
  /**
   * Not in use
   */
  MAGNETOMETER_X_RAW_16_HIGH_BYTE = 0x06,
  /**
   * Not in use
   */
  MAGNETOMETER_X_RAW_16_LOW_BYTE = 0x07,
  /**
   * Not in use
   */
  MAGNETOMETER_Y_RAW_16_HIGH_BYTE = 0x08,
  /**
   * Not in use
   */
  MAGNETOMETER_Y_RAW_16_LOW_BYTE = 0x09,
  /**
   * Not in use
   */
  MAGNETOMETER_Z_RAW_16_HIGH_BYTE = 0x0A,
  /**
   * Not in use
   */
  MAGNETOMETER_Z_RAW_16_LOW_BYTE = 0x0B,
  /**
   * Not in use
   */
  ACCELEROMETER_X_RAW_16_HIGH_BYTE = 0x0C,
  /**
   * Not in use
   */
  ACCELEROMETER_X_RAW_16_LOW_BYTE = 0x0D,
  /**
   * Not in use
   */
  ACCELEROMETER_Y_RAW_16_HIGH_BYTE = 0x0E,
  /**
   * Not in use
   */
  ACCELEROMETER_Y_RAW_16_LOW_BYTE = 0x0F,
  /**
   * Not in use
   */
  ACCELEROMETER_Z_RAW_16_HIGH_BYTE = 0x10,
  /**
   * Not in use
   */
  ACCELEROMETER_Z_RAW_16_LOW_BYTE = 0x11,
  /**
   * Not in use
   */
  GYRO_X_RAW_16_HIGH_BYTE = 0x12,
  /**
   * Not in use
   */
  GYRO_X_RAW_16_LOW_BYTE = 0x13,
  /**
   * Not in use
   */
  GYRO_Y_RAW_16_HIGH_BYTE = 0x14,
  /**
   * Not in use
   */
  GYRO_Y_RAW_16_LOW_BYTE = 0x15,
  /**
   * Not in use
   */
  GYRO_Z_RAW_16_HIGH_BYTE = 0x16,
  /**
   * Not in use
   */
  GYRO_Z_RAW_16_LOW_BYTE = 0x17,
  /**
   * Not in use
   */
  COMPASS_TEMPERATURE_16_HIGH_BYTE = 0x18,
  /**
   * Not in use
   */
  COMPASS_TEMPERATURE_16_LOW_BYTE = 0x19,
  /**
   * Compass bearing 16bit high byte degrees, used by CMPS12
   */
  COMPASS_BEARING_16_HIGH_BYTE_DEGREES = 0x1A,
  /**
   * Compass bearing 16bit low byte degrees, used by CMPS12
   */
  COMPASS_BEARING_16_LOW_BYTE_DEGREES = 0x1B,
  /**
   * Not in use
   */
  PITCH_ANGLE_16_HIGH_BYTE = 0x1C,
  /**
   * Not in use
   */
  PITCH_ANGLE_16_LOW_BYTE = 0x1D,
  /**
   * Calibration state 8bit, used by CMPS12
   */
  CALIBRATION_STATE_8 = 0x1E
} CMPS12I2CRegistry;

#endif // SAILINGBOAT_INCLUDE_CMPS12_I2C_REGISTRY_H_
