#include "doctest.h"
#include "../include/calculation_unit.h"
#include <iostream>
constexpr double CALCULATED_THRESHOLD = 0.005;

TEST_CASE("Test CalculationUnit") {
  CalculationUnit calculation_unit;

  GPSData waypoint1 = {60.0, 20.0};
  GPSData waypoint2 = {61.0, 21.0};
  GPSData boat_pos = waypoint1;
  double wind_angle = 40;
  double boat_heading = 50;

  bool isActive = true;
  while(isActive) {
    boat_pos.latitude += 0.1;
    boat_pos.longitude += 0.1;

    calculation_unit.SetBoatValues(waypoint1, waypoint2, boat_pos, wind_angle, boat_heading);
    calculation_unit.Calculate();
    double destination_distance = calculation_unit.CalculateDistance(boat_pos, waypoint2);
    if (destination_distance < CALCULATED_THRESHOLD) {
      std::cout << "Destination reached" << std::endl;
      isActive = false;
    }

    calculation_unit.Report();
    std::cout << "Distance to destination : " << destination_distance << std::endl;
  }
}
