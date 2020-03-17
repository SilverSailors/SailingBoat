#ifndef SAILINGBOAT_INCLUDE_GPS_H_
#define SAILINGBOAT_INCLUDE_GPS_H_
#include <libgpsmm.h>
#include <memory>
#include "gps_data.h"

class GPS {
 public:
  GPS();
  bool Init();
  GPSData Read();
 private:
  bool initialized_;
  ///
  ///GPSMM is an unique vector so we dont have
  ///to use the Init list to construct it,
  ///parameters will be passed in Init by make_unique<>()
  ///
  std::unique_ptr<gpsmm> gps_;
};

#endif // SAILINGBOAT_INCLUDE_GPS_H_
