#ifndef SAILINGBOAT_INCLUDE_MODULE_GPS_H_
#define SAILINGBOAT_INCLUDE_MODULE_GPS_H_
#include "gps.h"
#include "DataContainers/gps_data.h"

class ModuleGPS {
 public:
  /**
   * The constructor, initializes member fields
   */
  ModuleGPS();
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" object
   */
  bool GetInitialized();
  /**
   * Runs module, reads from hardware connection and saves it
   */
  void Run();
  /**
   * Returns "data_reading_" member field value
   * @return "data_reading_" object
   */
  GPSData GetReading();
  /**
   * Reports the latest reading
   */
  void Report();
 private:
  /**
   * Initialized, if ModuleCMPS12 is initialized
   */
  bool initialized_;
  /**
   * GPS Hardware connection, Hardware component for the module
   */
  GPS gps_hardware_connection_;
  /**
   * GPS data reading, the latest
   */
  GPSData data_reading_;
  /**
   * New data available for reading
   */
  bool new_data_available_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_GPS_H_
