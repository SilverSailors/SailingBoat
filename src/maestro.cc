#include "../include/maestro.h"
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
constexpr char PORT_NAME[] = "/dev/ttyACM0";

Maestro::Maestro() {
  // Initializes hardware connection
  file_descriptor_ = open(PORT_NAME, O_RDWR | O_NOCTTY);
  initialized_ = file_descriptor_ >= 0;

  // Configures options
  struct termios options;
  tcgetattr(file_descriptor_, &options);
  options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
  options.c_oflag &= ~(ONLCR | OCRNL);
  tcsetattr(file_descriptor_, TCSANOW, &options);
}

bool Maestro::GetInitialized() {
  return initialized_;
}

void Maestro::Command(unsigned char channel, unsigned char command, unsigned int value) {
  uint8_t mask = 0x7F;
  uint8_t value1 = value & mask;
  uint8_t value2 = (value >> 7u) & mask;

  // Initializes data array
  unsigned char data[] = {command, channel, value1, value2};

  if (write(file_descriptor_, data, sizeof(data)) == -1) {/* Writing error */}
}
