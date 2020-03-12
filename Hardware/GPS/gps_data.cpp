#include "gps_data.hpp"
#include <string>

GPSData::GPSData() {
  valid_ = false;
  latitude_ = 0;
  longitude_ = 0;
  speed_ = 0;
  time_ = "";
  time_value_ = 0;
}

void GPSData::SetLatitude(double latitude) {
  latitude_ = latitude;
}

void GPSData::SetLongitude(double longitude) {
  longitude_ = longitude;
}

void GPSData::SetTimestamp(std::string timestamp) {
  time_ = timestamp;
}

void GPSData::SetValid(bool valid) {
  valid_ = valid;
}

bool GPSData::GetValid() {
  return valid_;
}

double GPSData::GetLatitude() {
  return latitude_;
}

double GPSData::GetLongitude() {
  return longitude_;
}

std::string GPSData::GetTime() {
  return time_;
}

double GPSData::GetSpeed() {
  return speed_;
}

void GPSData::SetSpeed(double speed) {
  speed_ = speed;
}

void GPSData::SetTimeValue(double value) {
  time_value_ = value;
}

double GPSData::GetTimeValue() {
  return time_value_;
}
