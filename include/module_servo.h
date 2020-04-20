#ifndef SAILINGBOAT_INCLUDE_MODULE_SERVO_H_
#define SAILINGBOAT_INCLUDE_MODULE_SERVO_H_
#include "maestro.h"

class ModuleServo {
 public:
  /**
   * The constructor, initializes member fields
   * @param lower_limit Servo lower limit
   * @param upper_limit Servo upper limit
   * @param channel Channel to use
   */
  ModuleServo(double lower_limit, double upper_limit, int channel);
  /**
   * Returns "initialized_"
   * @return boolean on successful initialization
   */
  bool GetInitialized();
  /**
   * Runs module and writes to hardware connection
   */
  void Run();
  /**
   * Sets "target_" member field value based on limit and boundaries
   * @param limit Limit value
   */
  void SetTarget(double limit);
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
   * Upper boundary for servo
   */
  double upper_boundary_;
  /**
   * Lower boundary for servo
   */
  double lower_boundary_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_SERVO_H_
