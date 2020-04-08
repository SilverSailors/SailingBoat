#ifndef SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#define SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#include <queue>
#include <string>
#include "DataContainers/gps_data.h"

class ControlUnit {
 public:
  /**
   * The constructor, initializes member fields and reads destinations from file
   * @param destination Destinations
   */
  ControlUnit(std::string destination);
  /**
   * Returns "active_" member field value
   * @return "active_" boolean value
   */
  bool IsActive();
  /**
   * Returns first GPSData in "destination_" member field
   * @return GPSData object
   */
  GPSData GetDestination();
  /**
   * Returns "CALCULATED_THRESHOLD" define
   * @return "CALCULATED_THRESHOLD" value
   */
  double GetCalculatedThreshold();
  /**
   * Updates journey on a destination reached
   */
  void UpdateJourney();
 private:
  /**
   * Active, if there are destionations left
   */
  bool active_;
  /**
   * Destinations, queue of all our GPS destinations
   */
  std::queue<GPSData> destination_;
};

#endif // SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
