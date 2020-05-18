#ifndef SAILINGBOAT_INCLUDE_MODULE_COMPASS_H_
#define SAILINGBOAT_INCLUDE_MODULE_COMPASS_H_
#include "compass.h"

class ModuleCompass {
 public:
  /**
   * The constructor, initializes member fields
   */
  ModuleCompass();
  /**
   * Returns "initialized_"
   * @return boolean on successful initialization
   */
  bool GetInitialized();
  /**
   * Runs module, reads from hardware connection and saves it
   */
  void Run();
  /**
   * Returns "data_reading_" member field value
   * @return "data_reading_" value
   */
  int GetReading();
  /**
   * Reports the latest reading
   */
  void Report();
 private:
  /**
   * Hardware component for the module
   */
  Compass CMPS12_hardware_connection_;
  /**
   * The latest data reading
   */
  int data_reading_;
  /**
   * If ModuleCompass is initialized
   */
  bool initialized_;
  /**
   * New data available for reading
   */
  bool new_data_available_;
};

#endif //SAILINGBOAT_INCLUDE_MODULE_COMPASS_H_
