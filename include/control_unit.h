#ifndef SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#define SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#include <queue>
#include <string>
#include "DataContainers/gps_data.h"

class ControlUnit {
 public:
  /**
   * The constructor, initializes member fields and saves destinations read from file
   * @param destinations Destinations
   */
  ControlUnit(const std::string &destinations);
  /**
   * Returns "active_" member field value
   * @return "active_" boolean value
   */
  bool IsActive();
  /**
   * Returns first GPSData in "destinations_" member field
   * @return GPSData object
   */
  GPSData GetDestination();
  /**
   * Updates journey on a destination reached
   */
  void UpdateJourney();
 private:
  /**
   * If there are destinations left
   */
  bool active_;
  /**
   * Queue of all our GPS destinations
   */
  std::queue<GPSData> destinations_;
};

#endif // SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
