#ifndef __MODULE_CMPS12_HPP__
#define  __MODULE_CMPS12_HPP__
#include <vector>
#include "../../Hardware/CMPS12/CMPS12.hpp"
#include "../../Hardware/CMPS12/CMPS12_data.hpp"

class Module_CMPS12 {
 public:
  Module_CMPS12();
  ~Module_CMPS12();
  bool init();
  void run();
  bool getInitialized();
  CMPS12_DATA get_reading();
  void report();
  bool is_new_data_avilable();

 private:
  //Hardware component for our compass module
  CMPS12 m_CMPS12_hardware_connection;
  //Latest reading
  CMPS12_DATA m_CMPS12_data_reading;
  //Is this module initialized
  bool m_initialized;
  //Have we read the latest reading already?
  bool m_new_data_available;
  double m_internal_offset;
};

#endif//__MODULE_CMPS12_HPP__
