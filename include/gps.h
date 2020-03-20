#ifndef SAILINGBOAT_INCLUDE_GPS_H_
#define SAILINGBOAT_INCLUDE_GPS_H_
#include <libgpsmm.h>
#include <memory>
#include "gps_data.h"

class GPS {
 public:
  /**
   * The constructor
   */
  GPS();
  /**
   * Initializes and binds GPS to hardware
   * @return boolean value on successful initialization
   */
  bool Init();
  /**
   * Reads data from GPS component
   * @return Retrieved GPS data
   */
  GPSData Read();
 private:
  /**
   * Initialized, boolean value on GPS component initialized or not
   */
  bool initialized_;

  /**
   * Connection to GPS hardware, GPSMM is an unique vector
   */
  std::unique_ptr<gpsmm> gps_;
};

#endif // SAILINGBOAT_INCLUDE_GPS_H_
