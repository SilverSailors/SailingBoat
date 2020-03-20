#ifndef SAILINGBOAT_INCLUDE_MODULE_CMPS12_H_
#define SAILINGBOAT_INCLUDE_MODULE_CMPS12_H_
#include <vector>
#include "cmps12.h"
#include "cmps12_data.h"

class ModuleCMPS12 {
 public:
  /**
   * The constructor, initializes member fields
   */
  ModuleCMPS12();
  /**
   * The destructor
   */
  ~ModuleCMPS12();
  /**
   * Initializes "CMPS12_hardware_connection_"
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
  bool GetInitialized();
  /**
   * Returns "CMPS12_data_reading_" member field value
   * @return "CMPS12_data_reading_" object
   */
  CMPS12Data GetReading();
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
   * CMPS12 Hardware connection, Hardware component for the module
   */
  CMPS12 CMPS12_hardware_connection_;
  /**
   * CMPS12 Data reading, the latest
   */
  CMPS12Data CMPS12_data_reading_;
  /**
   * Initialized, if ModuleCMPS12 is initialized
   */
  bool initialized_;
  /**
   * New data available for reading
   */
  bool new_data_available_;
  /**
   * Internal offset for compass
   */
  double internal_offset_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_CMPS12_H_
