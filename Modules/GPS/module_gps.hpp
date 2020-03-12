#ifndef SAILINGBOAT_MODULES_MODULEGPS_MODULE_GPS_H_
#define SAILINGBOAT_MODULES_MODULEGPS_MODULE_GPS_H_
#include "../../Hardware/GPS/gps.hpp"
#include "../../Hardware/GPS/gps_data.hpp"

class ModuleGPS {
 public:
  ModuleGPS();
  bool Init();
  void Run();
  GPSData GetReading();
  void Report();
  bool IsNewDataAvilable();
 private:
  bool initialized_;
  GPS gps_hardware_connection_;
  GPSData data_reading_;
  //Have we Read the latest reading already?
  bool new_data_available_;
};

#endif // SAILINGBOAT_MODULES_MODULEGPS_MODULE_GPS_H_
