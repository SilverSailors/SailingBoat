#include "../include/module_servo.h"
#include "../include/utilities.h"
#include <iostream>

ModuleServo::ModuleServo(double lower_limit, double upper_limit, int channel) {
  upper_boundary_ = upper_limit;
  lower_boundary_ = lower_limit;
  channel_ = channel;
  initialized_ = false;
}

bool ModuleServo::Init() {
  bool result = servo_hardware_connection_.Init();
  initialized_ = result;
  if (result) {
    servo_hardware_connection_.Command(
        servo_hardware_connection_.GetFileDescriptor(),
        channel_,
        MAESTRO_SET_SPEED,
        50);
  }
  return result;
}

void ModuleServo::Run() {
  if (initialized_) {
    int servo_position = Utilities::ConvertCoordinates(
        upper_boundary_,
        lower_boundary_,
        servo_hardware_connection_.GetUpperLimit(),
        servo_hardware_connection_.GetLowerLimit(),
        target_);

    //std::cout << "TARGET IS: " << servo_position << std::endl;

    servo_hardware_connection_.Command(
        servo_hardware_connection_.GetFileDescriptor(),
        channel_,
        MAESTRO_SET_POSITION,
        servo_position);

  } else {
    std::cout << "Module_Servo not initialized" << std::endl;
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
