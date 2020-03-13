#ifndef SAILINGBOAT_MODULES_CMPS12_MODULE_CMPS12_H_
#define SAILINGBOAT_MODULES_CMPS12_MODULE_CMPS12_H_
#include <vector>
#include "../../Hardware/CMPS12/cmps12.h"
#include "../../Hardware/CMPS12/cmps12_data.h"

class ModuleCMPS12 {
 public:
  ModuleCMPS12();
  ~ModuleCMPS12();
  bool Init();
  void Run();
  bool GetInitialized();
  CMPS12Data GetReading();
  void Report();
  bool IsNewDataAvilable();
 private:
  //Hardware component for our compass module
  CMPS12 CMPS12_hardware_connection_;
  //Latest reading
  CMPS12Data CMPS12_data_reading_;
  //Is this module initialized
  bool initialized_;
  //Have we Read the latest reading already?
  bool new_data_available_;
  double internal_offset_;
};

#endif // SAILINGBOAT_MODULES_CMPS12_MODULE_CMPS12_H_
