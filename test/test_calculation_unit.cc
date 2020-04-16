#include "doctest.h"
#include "../include/calculation_unit.h"
#include <iostream>

TEST_CASE("Test CalculationUnit") {
  CalculationUnit cu;

  GPSData boat_pos = { };
  boat_pos.latitude = 60.0;
  boat_pos.longitude = 20.0;
  GPSData waypoint1 = boat_pos;
  GPSData waypoint2;
  waypoint2.latitude = 61.0;
  waypoint2.longitude = 21.0;

  double wind_angle = 40;
  double boat_heading = 50;

  while(1) {
    cu.SetBoatValues(waypoint1, waypoint2, boat_pos, wind_angle, boat_heading);
    cu.Calculate();
    cu.Report();

    // Update boat pos
    boat_pos.latitude += 0.1;
    boat_pos.longitude += 0.1;
    wind_angle += 10;

    double distance = cu.CalculateDistance(boat_pos, waypoint2);

    std::cout << "Distance to destination = " << distance << "\n";
    if(distance < 2.5) {
      std::cout << "Destination reached\n";
      break;
    }
  }
}
