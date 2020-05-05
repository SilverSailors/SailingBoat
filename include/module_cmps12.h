#ifndef SAILINGBOAT_INCLUDE_MODULE_CMPS12_H_
#define SAILINGBOAT_INCLUDE_MODULE_CMPS12_H_
#include "cmps12.h"

class ModuleCMPS12 {
 public:
  /**
   * The constructor, initializes member fields
   */
  ModuleCMPS12();
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
  CMPS12 CMPS12_hardware_connection_;
  /**
   * The latest data reading
   */
  int data_reading_;
  /**
   * If ModuleCMPS12 is initialized
   */
  bool initialized_;
  /**
   * New data available for reading
   */
  bool new_data_available_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_CMPS12_H_
