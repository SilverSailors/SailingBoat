#include <iostream>
#include "../Utilities/utilities.hpp"
#include "../Modules/CalculationUnit/calculation_unit.hpp"
#include <iomanip>
#include <vector>

int main(void) {
  CalculationUnit CU;

  GpsPosition start;
  start.latitude = 60.10347832490164;
  start.longitude = 19.928544759750366;

  GpsPosition destination;
  destination.latitude = 60.105879322635616;
  destination.longitude = 19.926559925079346;

  GpsPosition current_position = start;

  //Direction of wind in degrees
  double wind_bearing = 337;

  //How close do we need to be to the goal to finish
  double goal_threshold = 10.0;
  double distance_factor = 4.0;
  double calculated_threshold = goal_threshold / 1000;

  int side = 0;

  std::vector<GpsPosition> waypoint_log;

  waypoint_log.push_back(start);
  bool done = false;
  while (done == false) {
    //Get bearing to destination from current position
    double destination_bearing = Utilities::CoordinatesToDegrees(
        current_position.latitude, current_position.longitude,
        destination.latitude, destination.longitude);

    double AOA = 0;
    //Determine should we head left or right
    if (side == 0) {
      AOA = CU.CalculateAngleOfApproach(destination_bearing, wind_bearing);
      side = 1;
    } else {
      side = 0;
      AOA = Utilities::FlipDegrees(CU.CalculateAngleOfApproach(destination_bearing, wind_bearing));
    }

    //Add our current angle to the recommended one, normalized
    double waypoint_angle = Utilities::Normalize(AOA + destination_bearing);

    double goal_distance = CU.CalculateDistance(current_position, destination);

    double waypoint_distance = goal_distance / distance_factor;
    GpsPosition waypoint = CU.CalculateWaypoint(current_position, waypoint_distance, waypoint_angle);

    current_position.latitude = waypoint.latitude;
    current_position.longitude = waypoint.longitude;

    waypoint_log.push_back(waypoint);

    //std::cout << "Goal Distance: " << goal_distance << std::endl;
    //std::cout << "Goal Threshold: " << calculated_threshold << std::endl;
    if (goal_distance <= calculated_threshold) {
      std::cout << "GOAL REACHED" << std::endl;
      done = true;
    }

  }
  waypoint_log.push_back(destination);

  std::cout << "Waypoints Recorded: " << waypoint_log.size() << std::endl;

  for (int i = 0; i < waypoint_log.size(); i++) {
    std::cout << std::setprecision(20) << waypoint_log[i].latitude << "," << waypoint_log[i].longitude << std::endl;
  }

  return 0;
}
