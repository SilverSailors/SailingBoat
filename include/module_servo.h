#ifndef SAILINGBOAT_INCLUDE_MODULE_SERVO_H_
#define SAILINGBOAT_INCLUDE_MODULE_SERVO_H_
#include "maestro.h"

class ModuleServo {
 public:
  /**
   * The constructor, initializes member fields
   * @param lower_threshold Servo lower threshold
   * @param upper_threshold Servo upper threshold
   * @param channel Channel to use
   */
  ModuleServo(int lower_threshold, int upper_limit, int channel);
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" value
   */
  bool GetInitialized();
  /**
   * Runs module and writes to hardware connection
   */
  void Run();
  /**
   * Sets "target_" member field value based on limit and boundaries
   * @param "target_" value
   */
  void SetTarget(double target);
 private:
  /**
   * If ModuleServo is initialized
   */
  bool initialized_;
  /**
   * Channel to use
   */
  int channel_;
  /**
   * Hardware component for the module
   */
  Maestro servo_hardware_connection_;
  /**
   * Current servo position
   */
  double target_;
  /**
   * Upper threshold for servo
   */
  double upper_threshold_;
  /**
   * Lower threshold for servo
   */
  double lower_threshold_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_SERVO_H_
