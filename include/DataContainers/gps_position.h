#ifndef SAILINGBOAT_INCLUDE_DATACONTAINERS_GPS_POSITION_H_
#define SAILINGBOAT_INCLUDE_DATACONTAINERS_GPS_POSITION_H_

class GPSPosition {
 public:
  /**
   * The constructor, initializes member fields
   */
  GPSPosition();
  /**
   * Latitude coordinate
   */
  double latitude;
  /**
   * Longitude coordinate
   */
  double longitude;
};

#endif // SAILINGBOAT_INCLUDE_DATACONTAINERS_GPS_POSITION_H_
