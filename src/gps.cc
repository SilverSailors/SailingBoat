#include "../include/gps.h"
#include <iostream>
#include <cmath>
#include <string>

GPS::GPS() {
  std::cout << "Constructing [Hardware] GPS" << std::endl;
  // Init and bind
  gps_ = std::make_unique<gpsmm>("localhost", DEFAULT_GPSD_PORT);
  initialized_ = gps_ != nullptr &&
                 gps_->stream(WATCH_ENABLE | WATCH_JSON) != nullptr ? true : false;
}

bool GPS::GetInitialized() {
  if(!initialized_) {
    std::cout << "GPS HARDWARE FAILLLLLLLLL\n";
  }
  return initialized_;
}

GPSData GPS::Read() {
  GPSData gps_data;
  struct gps_data_t *gps_raw_data = gps_->read();

  if (gps_raw_data != nullptr) {
    gps_data.latitude = (std::isnan(gps_raw_data->fix.latitude)) ? -1.0 : gps_raw_data->fix.latitude;
    gps_data.longitude = (std::isnan(gps_raw_data->fix.longitude)) ? -1.0 : gps_raw_data->fix.longitude;
    /*time_t raw_time = gps_raw_data->fix.time.tv_sec;
    char timeiso[20];
    strftime(timeiso, sizeof(timeiso), "%Y-%m-%d-%H-%M-%S", localtime(&raw_time));
    std::string time_string(timeiso);
    */
    gps_data.timestamp = "2020-4-9";
  }
  return gps_data;
}
