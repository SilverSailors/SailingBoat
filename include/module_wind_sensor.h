#ifndef SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
#define SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
#include "ma3.h"

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
  MA3 hardware_connection_ma3_;
  int spi_channel_;
  int reading_;
  double internal_offset_;
  //Have we Read the latest reading already?
  bool new_data_available_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
