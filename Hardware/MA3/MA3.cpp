#include "MA3.hpp"
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>

MA3::MA3() {
  m_channel_config = 8;
}

bool MA3::init(int spi_channel) {
  //Load SPI Drivers (Not required as GPIO is native to PI)
  //And activated via Raspi-config instead
  //(Will output Warning text if run)

  /*
  if(system("gpio load spi") == -1)
  {
      std::cout << "Failed to load the GPIO SPI Drivers" << std::endl;
      return false;
  }
  */

  m_file_descriptor = wiringPiSPISetup(spi_channel, 1000000);
  if (m_file_descriptor < 0) {
    std::cout << "Failed to open SPI BUS" << std::endl;
    m_initialized = false;
    return m_initialized;
  }
  wiringPiSetup();
  m_initialized = true;
  return m_initialized;

}

int MA3::read(int spi_channel) {
  if (m_initialized) {
    unsigned char buffer[3] = {1};
    buffer[1] = (m_channel_config + 0) << 4;
    wiringPiSPIDataRW(spi_channel, buffer, 3);
    return ((buffer[1] & 3) << 8) + buffer[2];
  } else {
    std::cout << "Sensor not initialized!" << std::endl;
    return -1;
  }

}
