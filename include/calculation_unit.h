#ifndef SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#define SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#include "DataContainers/vec2.h"
#include "DataContainers/gps_position.h"

class CalculationUnit {
 public:
  /**
   * Calculates new position for rudder based on vector
   * @param vector Vec2 object
   * @return New rudder position
   */
  double CalculateRudderPosition(Vec2 vector);
  /**
   * Calculates new position for sail based on vector
   * @param vector Vec2 object
   * @return New sail position
   */
  double CalculateSailPosition(Vec2 vector);
  /**
   * Calculates new sailing angle of approach for boat, from destination- and wind-bearing
   * @param destination_bearing Destination bearing
   * @param wind_bearing Wind bearing
   * @return New sailing angle of approach
   */
  double CalculateAngleOfApproach(double destination_bearing, double wind_bearing);
  /**
   * Calculates a new target waypoint for the boat given distance ahead
   * @param current_position The current position
   * @param distance Target distance from current position
   * @param direction Target direction from current position
   * @return New waypoint with coordinates
   */
  GPSPosition CalculateWaypoint(GPSPosition current_position, double distance, double direction);
  /**
   * Calculates the distance between point A and B
   * @param point_a Point A
   * @param point_b Point B
   * @return Distance between the points
   */
  double CalculateDistance(GPSPosition point_a, GPSPosition point_b);
};

#endif // SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
