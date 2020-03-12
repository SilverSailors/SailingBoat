#ifndef SAILINGBOAT_MODULES_MODULESERVO_MODULE_SERVO_H_
#define SAILINGBOAT_MODULES_MODULESERVO_MODULE_SERVO_H_
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

#endif // SAILINGBOAT_MODULES_MODULESERVO_MODULE_SERVO_H_
