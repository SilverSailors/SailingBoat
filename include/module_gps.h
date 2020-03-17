#ifndef SAILINGBOAT_INCLUDE_MODULE_GPS_H_
#define SAILINGBOAT_INCLUDE_MODULE_GPS_H_
#include "gps.h"
#include "gps_data.h"

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
  ///
  ///Have we Read the latest reading already?
  ///
  bool new_data_available_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_GPS_H_
