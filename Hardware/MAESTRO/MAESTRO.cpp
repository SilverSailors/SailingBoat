#include "MAESTRO.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#define MAESTRO_SERVO_UPPER_LIMIT 8000
#define MAESTRO_SERVO_LOWER_LIMIT 3968

MAESTRO::MAESTRO() {
  //992 & 2000 respectively IN MCU (Maestro Control Unit)
  m_lower_limit = MAESTRO_SERVO_LOWER_LIMIT;
  m_upper_limit = MAESTRO_SERVO_UPPER_LIMIT;
  m_portname = "/dev/ttyACM0";
}

bool MAESTRO::init() {
  m_file_descriptor = open(m_portname, O_RDWR | O_NOCTTY);
  if (m_file_descriptor < 0) {
    std::cout << "Failed to open file descriptor" << std::endl;
    return false;
  }

  struct termios options;
  tcgetattr(m_file_descriptor, &options);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  options.c_oflag &= ~(ONLCR | OCRNL);
  tcsetattr(m_file_descriptor, TCSANOW, &options);

  return true;
}

void MAESTRO::command(int handle, unsigned char channel, MAESTRO_REGISTRY command, int target) {
  uint8_t mask = 0x7F;
  uint8_t value1 = target & mask;
  uint8_t value2 = (target >> 7) & mask;

  unsigned char data[] = {command, channel, value1, value2};

  if (write(handle, data, sizeof(data)) == -1) {
    std::cout << "ERROR WRITING COMMAND" << std::endl;
  }

}

int MAESTRO::get_file_descriptor() {
  return m_file_descriptor;
}

int MAESTRO::get_lower_limit() {
  return m_lower_limit;
}

int MAESTRO::get_upper_limit() {
  return m_upper_limit;
}
