#ifndef __GPS_HPP__
#define __GPS_HPP__
#include <libgpsmm.h>
#include <memory>
#include "GPS_data.hpp"

class GPS {
 public:
  GPS();
  bool init();
  GPS_DATA read();

 private:
  bool m_initialized;

  //GPSMM is an unique vector so we dont have
  //to use the init list to construct it,
  //parameters will be passed in init by make_unique<>()
  std::unique_ptr<gpsmm> m_gps;
};

#endif//__GPS_HPP__ 
