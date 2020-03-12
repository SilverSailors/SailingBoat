#ifndef __MODULE_CMPS12_HPP__
#define  __MODULE_CMPS12_HPP__
#include <vector>
#include "../../Hardware/Cmps12/cmps12.hpp"
#include "../../Hardware/Cmps12/cmps12_data.hpp"

class ModuleCmps12 {
 public:
  ModuleCmps12();
  ~ModuleCmps12();
  bool Init();
  void Run();
  bool GetInitialized();
  Cmps12Data GetReading();
  void Report();
  bool IsNewDataAvilable();
 private:
  //Hardware component for our compass module
  Cmps12 CMPS12_hardware_connection_;
  //Latest reading
  Cmps12Data CMPS12_data_reading_;
  //Is this module initialized
  bool initialized_;
  //Have we Read the latest reading already?
  bool new_data_available_;
  double internal_offset_;
};

#endif //__MODULE_CMPS12_HPP__
