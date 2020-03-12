#include "ma3.hpp"
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>

Ma3::Ma3() {
  channel_config_ = 8;
}

bool Ma3::Init(int spi_channel) {
  //Load SPI Drivers (Not required as GPIO is native to PI)
  //And activated via Raspi-config instead
  //(Will output Warning text if Run)

  /*
  if(system("gpio load spi") == -1)
  {
      std::cout << "Failed to load the GPIO SPI Drivers" << std::endl;
      return false;
  }
  */

  file_descriptor_ = wiringPiSPISetup(spi_channel, 1000000);
  if (file_descriptor_ < 0) {
    std::cout << "Failed to open SPI BUS" << std::endl;
    initialized_ = false;
    return initialized_;
  }
  wiringPiSetup();
  initialized_ = true;
  return initialized_;
}

int Ma3::Read(int spi_channel) {
  if (initialized_) {
    unsigned char buffer[3] = {1};
    buffer[1] = (channel_config_ + 0) << 4;
    wiringPiSPIDataRW(spi_channel, buffer, 3);
    return ((buffer[1] & 3) << 8) + buffer[2];
  } else {
    std::cout << "Sensor not initialized!" << std::endl;
    return -1;
  }
}
