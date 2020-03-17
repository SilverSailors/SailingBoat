#include "../include/maestro.h"
#include <termios.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include <fcntl.h>
#define MAESTRO_SERVO_UPPER_LIMIT 8000
#define MAESTRO_SERVO_LOWER_LIMIT 3968

Maestro::Maestro() {
  ///
  ///992 & 2000 respectively IN MCU (Maestro Control Unit)
  ///
  lower_limit_ = MAESTRO_SERVO_LOWER_LIMIT;
  upper_limit_ = MAESTRO_SERVO_UPPER_LIMIT;
  portname_ = "/dev/ttyACM0";
}

bool Maestro::Init() {
  file_descriptor_ = open(portname_, O_RDWR | O_NOCTTY);
  if (file_descriptor_ < 0) {
    std::cout << "Failed to open file descriptor" << std::endl;
    return false;
  }

  struct termios options;
  tcgetattr(file_descriptor_, &options);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  options.c_oflag &= ~(ONLCR | OCRNL);
  tcsetattr(file_descriptor_, TCSANOW, &options);

  return true;
}

void Maestro::Command(int handle, unsigned char channel, MaestroRegistry command, int value) {
  uint8_t mask = 0x7F;
  uint8_t value1 = value & mask;
  uint8_t value2 = (value >> 7) & mask;

  unsigned char data[] = {command, channel, value1, value2};

  if (write(handle, data, sizeof(data)) == -1) {
    std::cout << "ERROR WRITING COMMAND" << std::endl;
  }
}

int Maestro::GetFileDescriptor() {
  return file_descriptor_;
}

int Maestro::GetLowerLimit() {
  return lower_limit_;
}

int Maestro::GetUpperLimit() {
  return upper_limit_;
}
