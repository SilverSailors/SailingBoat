#include "../include/gps.h"
#include <cmath>
#include <string>

GPS::GPS() {
  // Make unique pointer to hardware
  gps_ = std::make_unique<gpsmm>("localhost", DEFAULT_GPSD_PORT);
  initialized_ = gps_ != nullptr &&
      gps_->stream(WATCH_ENABLE | WATCH_JSON) != nullptr ? true : false;
}

GPS::~GPS() {
  gps_->stream(WATCH_DISABLE);
}

bool GPS::GetInitialized() {
  return initialized_;
}

GPSData GPS::Read() {
  GPSData gps_data;
  struct gps_data_t *gps_raw_data = gps_->read();

  // If read was OK, saves values into our GPSData
  if (gps_raw_data != nullptr && gps_raw_data->status == STATUS_FIX && !std::isnan(gps_raw_data->fix.latitude)
      && !std::isnan(gps_raw_data->fix.latitude)) {
    gps_data.latitude = gps_raw_data->fix.latitude;
    gps_data.longitude = gps_raw_data->fix.longitude;
    time_t raw_time = gps_raw_data->fix.time;
    char timeiso[20];
    strftime(timeiso, sizeof(timeiso), "%Y-%m-%d-%H-%M-%S", localtime(&raw_time));
    std::string time_string(timeiso);
    gps_data.timestamp = time_string;
  }
  return gps_data;
}
