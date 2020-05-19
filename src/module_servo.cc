#include "../include/module_servo.h"
#include "../include/calculation_unit.h"
#include <cmath>
constexpr int MAESTRO_SET_POSITION = 0x84;
constexpr int MAESTRO_SET_SPEED = 0x87;
constexpr int MAESTRO_SERVO_UPPER_THRESHOLD = 8000;
constexpr int MAESTRO_SERVO_LOWER_THRESHOLD = 3968;

ModuleServo::ModuleServo(int lower_threshold, int upper_threshold, int channel) {
  lower_threshold_ = lower_threshold;
  upper_threshold_ = upper_threshold;
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
    int servo_position = (int) round(CalculationUnit::ConvertCoordinates(
        upper_threshold_,
        lower_threshold_,
        MAESTRO_SERVO_UPPER_THRESHOLD,
        MAESTRO_SERVO_LOWER_THRESHOLD,
        target_
    ));

    // Updates servo position
    servo_hardware_connection_.Command(
        channel_,
        MAESTRO_SET_POSITION,
        servo_position
    );
  }
}

void ModuleServo::SetTarget(double target) {
  if (target < upper_threshold_ || target > lower_threshold_) {
    target_ = target;
  } else if (target > upper_threshold_) {
    target_ = upper_threshold_;
  } else if (target < lower_threshold_) {
    target_ = lower_threshold_;
  }
}
