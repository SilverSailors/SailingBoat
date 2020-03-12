#ifndef __GPS_HPP__
#define __GPS_HPP__
#include <libgpsmm.h>
#include <memory>
#include "gps_data.hpp"

class Gps {
 public:
  Gps();
  bool Init();
  GpsData Read();
 private:
  bool initialized_;
  //GPSMM is an unique vector so we dont have
  //to use the Init list to construct it,
  //parameters will be passed in Init by make_unique<>()
  std::unique_ptr<gpsmm> gps_;
};

#endif //__GPS_HPP__
