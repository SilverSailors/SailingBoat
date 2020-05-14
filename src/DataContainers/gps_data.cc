#include "../../include/DataContainers/gps_data.h"

GPSData GPSData::operator+(const GPSData &gps_data) {
  GPSData new_data;
  new_data.latitude = this->latitude + gps_data.latitude;
  new_data.longitude = this->longitude + gps_data.longitude;
  new_data.timestamp = gps_data.timestamp;
  return new_data;
}

GPSData GPSData::operator-(const GPSData &gps_data) {
  GPSData new_data;
  new_data.latitude = this->latitude - gps_data.latitude;
  new_data.longitude = this->longitude - gps_data.longitude;
  new_data.timestamp = gps_data.timestamp;
  return new_data;
}

GPSData GPSData::operator/(int scalar) {
  GPSData new_data;
  new_data.latitude = this->latitude / scalar;
  new_data.longitude = this->longitude / scalar;
  new_data.timestamp = this->timestamp;
  return new_data;
}

