#ifndef SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#define SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#include <queue>
#include <string>
#include <vector>
#include "DataContainers/gps_position.h"
#include "angle.h"

class ControlUnit {
 public:
  /**
   * The constructor, initializes member fields
   */
  ControlUnit();
  /**
   * Returns "active_" member field value
   * @return "active_" boolean value
   */
  bool IsActive();
  /**
   * Initializes ControlUnit from destination and settings files and logs beginning of journey
   * @param destination destination file path
   * @param settings settings file path
   * @return boolean value on successfully initialized
   */
  bool Init(std::string destination, std::string settings);
  /**
   * Returns first GPSPosition in "destination_" member field
   * @return GPSPosition object
   */
  GPSPosition GetDestination();
  /**
   * Not in use
   * @param destination
   */
  void SetDestination(GPSPosition destination);
  /**
   * Returns "waypoint_" member field value
   * @return "waypoint_" GPSPosition object
   */
  GPSPosition GetWaypoint();
  /**
   * Sets and updates "waypoint_" and "waypoint_set_" member fields
   * @param waypoint GPSPosition object
   */
  void SetWaypoint(GPSPosition waypoint);
  /**
   * Not in use
   * @param value
   */
  void SetDistanceThreshold(double value);
  /**
   * Not in use
   * @return
   */
  double GetDistanceThreshold();
  /**
   * Validates all module statuses
   * @param statuses boolean Vector with statuses
   * @return boolean value on successful validation
   */
  bool ValidateInits(std::vector<bool> statuses);
  /**
   * Returns "waypoint_set_" member field value
   * @return "waypoint_set_" boolean value
   */
  bool IsWaypointSet();
  /**
   * Sets "waypoint_set_" member field value
   * @param status Boolean value
   */
  void SetWaypointStatus(bool status);
  /**
   * Alternates current boat angle side
   */
  void AlternateAngle();
  /**
   * Returns "angle_direction_" member field value
   * @return "angle_direction_" value
   */
  Angle GetAngleDirection();
  /**
   * Returns "distance_factor_" member field value
   * @return "distance_factor_" value
   */
  double GetDistanceFactor();
  /**
   * Returns if time limit for reaching new waypoint is reached
   * @param time_value Time as integer
   * @return boolean value on time limit reached
   */
  bool TimeDiscrepencyReached(int time_value);
  /**
   * Sets "time_value_" member field value
   * @param value Time value as integer
   */
  void SetTimeValue(int value);
  /**
   * Returns "calculated_threshold_" member field value
   * @return "calculated_threshold_" value
   */
  double GetCalculatedThreshold();
  /**
   * Updates journey on a destination reached
   */
  void UpdateJourney();
  /**
   * Returns "waypoint_distance_creation_threshold_" member field value
   * @return "waypoint_distance_creation_threshold_" value
   */
  double GetWaypointCreationThreshold();
 private:
  /**
   * Active, if the ControlUnit is active
   */
  bool active_;
  /**
   * Not in use
   */
  bool waypoint_reached_;
  /**
   * Waypoint set, if we have set a waypoint?
   */
  bool waypoint_set_;
  /**
   * Not in use
   */
  bool destination_set_;
  /**
   * Not in use
   */
  bool destination_reached_;
  /**
   * Destinations, queue of all our GPS destinations
   */
  std::queue<GPSPosition> destination_;
  /**
   * Waypoint, as a GPSPosition object
   */
  GPSPosition waypoint_;
  /**
   * Distance threshold, distance in meters away from waypoint to consider it reached
   */
  double distance_threshold_;
  /**
   * Time threshold, time until establishing a new waypoint if old one hasn't been reached
   */
  double time_threshold_;
  /**
   * Distance factor, how far away from initial position should waypoints be
   */
  double distance_factor_;
  /**
   * Time value, time as number
   */
  double time_value_;
  /**
   * Calculated threshold, calculated value from "distance_threshold_" member field value
   */
  double calculated_threshold_;
  /**
   * Waypoint distance creation threshold
   */
  double waypoint_distance_creation_threshold_;
  /**
   * Boat angle direction side
   */
  Angle angle_direction_;
};

#endif // SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
