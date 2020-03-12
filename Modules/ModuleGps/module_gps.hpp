#ifndef __MODULE_GPS_HPP__
#define __MODULE_GPS_HPP__
#include "../../Hardware/Gps/gps.hpp"
#include "../../Hardware/Gps/gps_data.hpp"

class ModuleGps {
 public:
  ModuleGps();
  bool Init();
  void Run();
  GpsData GetReading();
  void Report();
  bool IsNewDataAvilable();
 private:
  bool initialized_;
  Gps gps_hardware_connection_;
  GpsData data_reading_;
  //Have we Read the latest reading already?
  bool new_data_available_;
};

#endif //__MODULE_GPS_HPP__
