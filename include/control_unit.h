#ifndef SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#define SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
#include <queue>
#include <string>
#include <vector>
#include "DataContainers/gps_position.h"
#include "angle.h"

class ControlUnit {
 public:
  ControlUnit();
  bool IsActive();
  bool Init(std::string destination, std::string settings);
  GPSPosition GetDestination();
  void SetDestination(GPSPosition destination);
  GPSPosition GetWaypoint();
  void SetWaypoint(GPSPosition waypoint);
  void SetDistanceThreshold(double value);
  double GetDistanceThreshold();
  bool ValidateInits(std::vector<bool> statuses);
  bool IsWaypointSet();
  void SetWaypointStatus(bool status);
  void AlternateAngle();
  Angle GetAngleDirection();
  double GetDistanceFactor();
  bool TimeDiscrepencyReached(int time_value);
  void SetTimeValue(int value);
  double GetCalculatedThreshold();
  void UpdateJourney();
  double GetWaypointCreationThreshold();
 private:
  bool active_;                     //Is the Control Unit Activated
  bool waypoint_reached_;           //Have we reached our waypoint
  bool waypoint_set_;               //Have we set a waypoint?
  bool destination_set_;            //Have we set a destination
  bool destination_reached_;        //Have we reached our destination
  std::queue<GPSPosition> destination_;                //Queue of all our destinations
  GPSPosition waypoint_;                   //Our current waypoint
  double distance_threshold_;         //The distance we are allowed to be away from the waypoint to consider it reached (Meters)
  double time_threshold_;             //How long should we wait until we establish a new waypoint If the old one hasnt been reached
  double distance_factor_;            //How far away should waypoints be from our initial position
  double time_value_;
  double calculated_threshold_;
  double waypoint_distance_creation_threshold_;
  Angle angle_direction_;
};

#endif // SAILINGBOAT_INCLUDE_CONTROL_UNIT_H_
