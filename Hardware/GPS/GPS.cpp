#include "GPS.hpp"
#include <iostream>
#include <math.h>
#include <string>

GPS::GPS() {

}

bool GPS::init() {
  //Init and bind
  m_gps = std::make_unique<gpsmm>("localhost", DEFAULT_GPSD_PORT);

  if (m_gps == nullptr) {
    std::cout << "Failed to bind GPS with gpsmm" << std::endl;
    return false;
  }

  //Check if our DAEMON is running
  if (m_gps->stream(WATCH_ENABLE | WATCH_JSON) == nullptr) {
    std::cout << "GPSD DAEMON NOT RUNNING" << std::endl;
    return false;
  }

  return true;

}

GPS_DATA GPS::read() {
  GPS_DATA data_reading;

  struct gps_data_t *gps_raw_data;

  if ((gps_raw_data = m_gps->read()) == nullptr) {
    std::cout << "READ ERROR: CHECK USB PORT NAME FOR GPSD" << std::endl;
  } else {
    double lat = gps_raw_data->fix.latitude;
    double lon = gps_raw_data->fix.longitude;

    if (isnan(lat) || isnan(lon)) {
      std::cout << "READ ERROR (Too Fast Readings/Indoors?)" << std::endl;
      return data_reading;
    } else {
      time_t raw_time = gps_raw_data->fix.time.tv_sec;
      char timeiso[20];
      strftime(timeiso, sizeof(timeiso), "%Y-%m-%d-%H-%M-%S", localtime(&raw_time));

      //RESET

      std::string time_string(timeiso);
      long int time_reading = static_cast<int>(raw_time);

      //std::cout << "Time: " << time_string << std::endl;
      //std::cout << "Time: " << time_reading << std::endl;

      data_reading.set_valid(true);
      data_reading.set_latitude(gps_raw_data->fix.latitude);
      data_reading.set_longitude(gps_raw_data->fix.longitude);
      data_reading.set_speed(gps_raw_data->fix.speed);
      data_reading.set_time_value(time_reading);
      data_reading.set_timestamp(time_string);
      return data_reading;
    }
  }

  return data_reading;
}
