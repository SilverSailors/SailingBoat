#ifndef SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
#define SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
#include "ma3.h"

class ModuleWindSensor {
 public:
  /**
   * The constructor, initializes member fields
   * @param spi_channel Spi channel
   */
  ModuleWindSensor(int spi_channel);
  /**
   * Initializes "hardware_connection_ma3_"
   * @return boolean on successful initialization
   */
  bool Init();
  /**
   * Runs module, reads from hardware connection and saves it
   */
  void Run();
  /**
   * Not in use
   * @return
   */
  int GetReading();
  /**
   * Not in use
   */
  void Report();
  /**
   * Not in use
   * @return
   */
  bool IsNewDataAvailable();
 private:
  /**
   * Initialized, if ModuleWindSensor is initialized
   */
  bool initialized_;
  /**
   * MA3 Hardware connection, Hardware component for the module
   */
  MA3 hardware_connection_ma3_;
  /**
   * SPI channel to use
   */
  int spi_channel_;
  /**
   * Reading, the latest
   */
  int reading_;
  /**
   * Internal offset for wind sensor
   */
  double internal_offset_;
  /**
   * New data available for reading
   */
  bool new_data_available_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
