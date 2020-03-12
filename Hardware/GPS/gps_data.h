#ifndef SAILINGBOAT_HARDWARE_GPS_GPS_DATA_H_
#define SAILINGBOAT_HARDWARE_GPS_GPS_DATA_H_
#include <string>

class GPSData {
 public:
  GPSData();
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

#endif // SAILINGBOAT_HARDWARE_GPS_GPS_DATA_H_
