#ifndef __MODULE_WIND_SENSOR_HPP__
#define __MODULE_WIND_SENSOR_HPP__
#include "../../Hardware/Ma3/ma3.hpp"

class ModuleWindSensor {
 public:
  ModuleWindSensor(int spi_channel);
  bool Init();
  void Run();
  int GetReading();
  void Report();
  bool IsNewDataAvailable();
 private:
  bool initialized_;
  Ma3 hardware_connection_ma3_;
  int spi_channel_;
  int reading_;
  double internal_offset_;
  //Have we Read the latest reading already?
  bool new_data_available_;
};

#endif //__MODULE_WIND_SENSOR_HPP__
