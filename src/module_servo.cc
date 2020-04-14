#include "../include/module_servo.h"
#include "../include/calculation_unit.h"
#include <iostream>
#define MAESTRO_SET_POSITION 0x84
#define MAESTRO_SET_SPEED 0x87
#define MAESTRO_SERVO_UPPER_LIMIT 8000
#define MAESTRO_SERVO_LOWER_LIMIT 3968

ModuleServo::ModuleServo(double lower_limit, double upper_limit, int channel) {
  std::cout << "Constructing [Module] Servo" << std::endl;
  upper_boundary_ = upper_limit;
  lower_boundary_ = lower_limit;
  channel_ = channel;
  initialized_ = servo_hardware_connection_.GetInitialized();
  if (initialized_) {
    servo_hardware_connection_.Command(
      channel_,
      MAESTRO_SET_SPEED,
      50
    );
  }
}

bool ModuleServo::GetInitialized() {
  if (!initialized_) std::cout << "[Module] Servo not initialized" << std::endl;
  return initialized_;
}

void ModuleServo::Run() {
  if (initialized_) {
    int servo_position = CalculationUnit::ConvertCoordinates(
      upper_boundary_,
      lower_boundary_,
      MAESTRO_SERVO_UPPER_LIMIT,
      MAESTRO_SERVO_LOWER_LIMIT,
      target_
    );

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
