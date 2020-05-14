#include "doctest.h"
#include "../include/calculation_unit.h"
#include <iostream>

TEST_CASE ("Test CalculationUnit") {
  CalculationUnit calculation_unit;

  GPSData waypoint1 = {60.103093, 19.861749};
  GPSData waypoint2 = {60.103650, 19.863887};
  GPSData boat_pos = {60.102992, 19.863860};
  int wind_angle = 270;
  int boat_heading = 0;

  calculation_unit.SetBoatValues(waypoint1, waypoint2, boat_pos, wind_angle, boat_heading);
  calculation_unit.Calculate();

  std::cout << "Route angle : " << calculation_unit.GetRouteAngle() << std::endl;
  std::cout << "Rudder angle : " << calculation_unit.GetRudderAngle() << std::endl;
  std::cout << "Sail angle : " << calculation_unit.GetSailAngle() << std::endl;
}
