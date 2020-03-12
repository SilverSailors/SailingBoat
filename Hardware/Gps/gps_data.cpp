#include "gps_data.hpp"
#include <string>

GpsData::GpsData() {
  valid_ = false;
  latitude_ = 0;
  longitude_ = 0;
  speed_ = 0;
  time_ = "";
  time_value_ = 0;
}

void GpsData::SetLatitude(double latitude) {
  latitude_ = latitude;
}

void GpsData::SetLongitude(double longitude) {
  longitude_ = longitude;
}

void GpsData::SetTimestamp(std::string timestamp) {
  time_ = timestamp;
}

void GpsData::SetValid(bool valid) {
  valid_ = valid;
}

bool GpsData::GetValid() {
  return valid_;
}

double GpsData::GetLatitude() {
  return latitude_;
}

double GpsData::GetLongitude() {
  return longitude_;
}

std::string GpsData::GetTime() {
  return time_;
}

double GpsData::GetSpeed() {
  return speed_;
}

void GpsData::SetSpeed(double speed) {
  speed_ = speed;
}

void GpsData::SetTimeValue(double value) {
  time_value_ = value;
}

double GpsData::GetTimeValue() {
  return time_value_;
}
