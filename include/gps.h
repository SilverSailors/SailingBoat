#ifndef SAILINGBOAT_INCLUDE_GPS_H_
#define SAILINGBOAT_INCLUDE_GPS_H_
#include <libgpsmm.h>
#include <memory>
#include "DataContainers/gps_data.h"

class GPS {
 public:
  /**
   * The constructor, initializes and binds GPS to hardware
   */
  GPS();
  /**
   * The destructor, closes gps connection
   */
  ~GPS();
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" object
   */
  bool GetInitialized();
  /**
   * Reads data from GPS component
   * @return Retrieved GPS data
   */
  GPSData Read();
 private:
  /**
   * If component is initialized
   */
  bool initialized_;
  /**
   * Connection to GPS hardware
   */
  std::unique_ptr<gpsmm> gps_;
};

#endif // SAILINGBOAT_INCLUDE_GPS_H_
