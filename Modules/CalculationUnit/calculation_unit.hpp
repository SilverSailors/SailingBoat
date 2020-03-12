#ifndef __CALCULATION_UNIT_HPP__
#define __CALCULATION_UNIT_HPP__
#include "../../Utilities/DataContainers/vec2.hpp"
#include "../../Utilities/DataContainers/gps_position.hpp"

class CalculationUnit {
 public:
  double CalculateRudderPosition(Vec2 vector);
  double CalculateSailPosition(Vec2 vector);
  double CalculateAngleOfApproach(double destination_bearing, double wind_bearing);
  GpsPosition CalculateWaypoint(GpsPosition current_position, double distance, double direction);
  double CalculateDistance(GpsPosition point_a, GpsPosition point_b);
};

#endif //__CALCULATION_UNIT_HPP__
