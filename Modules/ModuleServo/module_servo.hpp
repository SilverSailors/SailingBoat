#ifndef __MODULE_SERVO_HPP__
#define __MODULE_SERVO_HPP__
#include "../../Hardware/Maestro/maestro.hpp"

class ModuleServo {
 public:
  ModuleServo(double lower_limit, double upper_limit, int channel);
  bool Init();
  void Run();
  void SetTarget(double limit);
 private:
  bool initialized_;
  double upper_boundary_;
  double lower_boundary_;
  int channel_;
  double target_;
  Maestro servo_hardware_connection_;
};

#endif //__MODULE_SERVO_HPP__
