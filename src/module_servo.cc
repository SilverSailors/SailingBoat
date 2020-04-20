#include "../include/module_servo.h"
#include "../include/calculation_unit.h"
#define MAESTRO_SET_POSITION 0x84
#define MAESTRO_SET_SPEED 0x87
#define MAESTRO_SERVO_UPPER_LIMIT 8000
#define MAESTRO_SERVO_LOWER_LIMIT 3968

ModuleServo::ModuleServo(double lower_limit, double upper_limit, int channel) {
  lower_boundary_ = lower_limit;
  upper_boundary_ = upper_limit;
  channel_ = channel;
  initialized_ = servo_hardware_connection_.GetInitialized();
  if (initialized_) {
    // Sets the speed limit for value updates
    servo_hardware_connection_.Command(
      channel_,
      MAESTRO_SET_SPEED,
      50
    );
  }
}

bool ModuleServo::GetInitialized() {
  return initialized_;
}

void ModuleServo::Run() {
  if (initialized_) {
    // Converts to value usable by hardware
    int servo_position = CalculationUnit::ConvertCoordinates(
      upper_boundary_,
      lower_boundary_,
      MAESTRO_SERVO_UPPER_LIMIT,
      MAESTRO_SERVO_LOWER_LIMIT,
      target_
    );

    // Updates servo position
    servo_hardware_connection_.Command(
      channel_,
      MAESTRO_SET_POSITION,
      servo_position
    );
  }
}

void ModuleServo::SetTarget(double limit) {
  if (limit < upper_boundary_ || limit > lower_boundary_) {
    target_ = limit;
  } else if (limit > upper_boundary_) {
    target_ = upper_boundary_;
  } else if (limit < lower_boundary_) {
    target_ = lower_boundary_;
  }
}
