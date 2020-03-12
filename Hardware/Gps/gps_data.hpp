#ifndef __GPS_DATA_HPP__
#define __GPS_DATA_HPP__
#include <string>

class GpsData {
 public:
  GpsData();
  void SetLatitude(double latitude);
  void SetLongitude(double longitude);
  void SetTimestamp(std::string timestamp);
  void SetTimeValue(double value);
  void SetValid(bool valid);
  bool GetValid();
  double GetLatitude();
  double GetLongitude();
  std::string GetTime();
  double GetTimeValue();
  void SetSpeed(double speed);
  double GetSpeed();
 private:
  bool valid_;
  double latitude_;
  double longitude_;
  double speed_;
  long int time_value_;
  std::string time_;
};

#endif //__GPS_DATA_HPP__
