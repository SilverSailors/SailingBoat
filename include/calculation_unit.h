#ifndef SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#define SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#include "DataContainers/vec2.h"
#include "DataContainers/gps_position.h"

class CalculationUnit {
 public:
  double CalculateRudderPosition(Vec2 vector);
  double CalculateSailPosition(Vec2 vector);
  double CalculateAngleOfApproach(double destination_bearing, double wind_bearing);
  GPSPosition CalculateWaypoint(GPSPosition current_position, double distance, double direction);
  double CalculateDistance(GPSPosition point_a, GPSPosition point_b);
};

#endif // SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
