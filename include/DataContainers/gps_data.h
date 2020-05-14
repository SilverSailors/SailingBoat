#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_GPS_DATA_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_GPS_DATA_H_
#include <string>

struct GPSData {
  double latitude;
  double longitude;
  std::string timestamp;
  GPSData operator+(const GPSData &gps_data);
  GPSData operator-(const GPSData &gps_data);
  GPSData operator/(int scalar);
};

#endif //SAILINGBOAT_INCLUDE_DATACONTAINERS_GPS_DATA_H_
