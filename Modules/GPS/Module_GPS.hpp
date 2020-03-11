#ifndef __MODULE_GPS_HPP__
#define __MODULE_GPS_HPP__
#include "../../Hardware/GPS/GPS.hpp"
#include "../../Hardware/GPS/GPS_data.hpp"

class Module_GPS {
 public:
  Module_GPS();
  bool init();
  void run();
  GPS_DATA get_reading();
  void report();
  bool is_new_data_avilable();

 private:
  bool m_initialized;
  GPS m_gps_hardware_connection;
  GPS_DATA m_data_reading;
  //Have we read the latest reading already?
  bool m_new_data_available;
};

#endif //__MODULE_GPS_HPP__
