#include "Module_SERVO.hpp"
#include "../../Utilities/utilities.hpp"
#include <iostream>

Module_SERVO::Module_SERVO(double lower_limit, double upper_limit, int channel) {
  m_upper_boundary = upper_limit;
  m_lower_boundary = lower_limit;
  m_channel = channel;
  m_initialized = false;
}

bool Module_SERVO::init() {
  bool result = m_servo_hardware_connection.init();
  m_initialized = result;
  if (result) {
    m_servo_hardware_connection.command(
        m_servo_hardware_connection.get_file_descriptor(),
        m_channel,
        MAESTRO_SET_SPEED,
        50);
  }
  return result;
}

void Module_SERVO::run() {
  if (m_initialized) {
    int servo_position = Utilities::convert_coordinates(
        m_upper_boundary,
        m_lower_boundary,
        m_servo_hardware_connection.get_upper_limit(),
        m_servo_hardware_connection.get_lower_limit(),
        m_target);

    //std::cout << "TARGET IS: " << servo_position << std::endl;

    m_servo_hardware_connection.command(
        m_servo_hardware_connection.get_file_descriptor(),
        m_channel,
        MAESTRO_SET_POSITION,
        servo_position);

  } else {
    std::cout << "Module_Servo not initialized" << std::endl;
  }
}

void Module_SERVO::set_target(double limit) {
  if (limit < m_upper_boundary || limit > m_lower_boundary) {
    m_target = limit;
  } else if (limit > m_upper_boundary) {
    m_target = m_upper_boundary;
  } else if (limit < m_lower_boundary) {
    m_target = m_lower_boundary;
  }
}
