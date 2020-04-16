#include "../include/maestro.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#define PORT_NAME "/dev/ttyACM0"
#define MAESTRO_SERVO_UPPER_LIMIT 8000
#define MAESTRO_SERVO_LOWER_LIMIT 3968

Maestro::Maestro() {
  file_descriptor_ = open(PORT_NAME, O_RDWR | O_NOCTTY);
  initialized_ = file_descriptor_ >= 0;

  struct termios options;
  tcgetattr(file_descriptor_, &options);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  options.c_oflag &= ~(ONLCR | OCRNL);
  tcsetattr(file_descriptor_, TCSANOW, &options);
}

bool Maestro::GetInitialized() {
  return initialized_;
}

void Maestro::Command(unsigned char channel, unsigned char command, int value) {
  uint8_t mask = 0x7F;
  uint8_t value1 = value & mask;
  uint8_t value2 = (value >> 7) & mask;

  unsigned char data[] = {command, channel, value1, value2};

  if (write(file_descriptor_, data, sizeof(data)) == -1) {} // ERROR WRITING
}

int Maestro::GetUpperLimit() {
  return MAESTRO_SERVO_UPPER_LIMIT;
}

int Maestro::GetLowerLimit() {
  return MAESTRO_SERVO_LOWER_LIMIT;
}
