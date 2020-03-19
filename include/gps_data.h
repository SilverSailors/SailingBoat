#ifndef SAILINGBOAT_INCLUDE_GPS_DATA_H_
#define SAILINGBOAT_INCLUDE_GPS_DATA_H_
#include <string>

class GPSData {
 public:
  /**
   * The constructor, initializes member fields
   */
  GPSData();
  /**
   * Sets "latitude_" member field value
   * @param latitude Latitude value
   */
  void SetLatitude(double latitude);
  /**
   * Sets "longitude_" member field value
   * @param longitude Longitude value
   */
  void SetLongitude(double longitude);
  /**
   * Sets "time_" member field value
   * @param timestamp Timestamp value
   */
  void SetTimestamp(std::string timestamp);
  /**
   * Sets "time_value_" member field value
   * @param value Time as integer
   */
  void SetTimeValue(double value);
  /**
   * Sets "valid_" member field value
   * @param valid Boolean value
   */
  void SetValid(bool valid);
  /**
   * Returns "valid_" member field value
   * @return "valid_" boolean value
   */
  bool GetValid();
  /**
   * Returns "latitude_" member field value
   * @return "latitude_" value
   */
  double GetLatitude();
  /**
   * Returns "longitude_" member field value
   * @return "longitude_" value
   */
  double GetLongitude();
  /**
   * Returns "time_" member field value
   * @return "time_" value
   */
  std::string GetTime();
  /**
   * Returns "time_value_" member field value
   * @return "time_value_" value
   */
  double GetTimeValue();
  /**
   * Sets "speed_" member field value
   * @param speed speed value
   */
  void SetSpeed(double speed);
  /**
   * Returns "speed_" member field value
   * @return "speed_" value
   */
  double GetSpeed();
 private:
  /**
   * Valid, if GPSData valid
   */
  bool valid_;
  /**
   * Latitude coordinate
   */
  double latitude_;
  /**
   * Longitude coordinate
   */
  double longitude_;
  /**
   * Speed, Movement speed
   */
  double speed_;
  /**
   * Time value, as integer
   */
  long int time_value_;
  /**
   * Time
   */
  std::string time_;
};

#endif // SAILINGBOAT_INCLUDE_GPS_DATA_H_
