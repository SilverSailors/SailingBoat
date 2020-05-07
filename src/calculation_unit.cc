#include "../include/calculation_unit.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
constexpr int EARTH_RADIUS = 6371;
constexpr double BOAT_TO_LINE_MAX_DISTANCE = 25;
constexpr int RUDDER_MAX_ANGLE = 1;
constexpr int SAIL_MAX_ANGLE = 1;
constexpr double INCIDENCE_ANGLE = M_PI / 4;
constexpr double CLOSED_HAUL_ANGLE = M_PI / 3;

void CalculationUnit::SetBoatValues(GPSData waypoint_1,
                                    GPSData waypoint_2,
                                    GPSData boat_pos,
                                    int wind_angle,
                                    int boat_heading) {
  waypoint_1_ = std::move(waypoint_1);
  waypoint_2_ = std::move(waypoint_2);
  boat_pos_ = std::move(boat_pos);
  wind_angle_ = DegreesToRadians(wind_angle);
  boat_heading_ = DegreesToRadians(boat_heading);
}

void CalculationUnit::Calculate() {
  CalculateDistanceFromBoatToLine();
  CheckTackVariable();
  CalculateAngleOfLine();
  CalculateNominalAngle();
  CalculateBoatDirection();
  CalculateRudderAngle();
  CalculateSailAngle();
}

void CalculationUnit::CalculateDistanceFromBoatToLine() {
  GPSData waypoint = waypoint_2_ - waypoint_1_;
  double magnitude = sqrt(pow(waypoint.latitude, 2) + pow(waypoint.longitude, 2));

  GPSData position_1 = {waypoint.latitude / magnitude, waypoint.longitude / magnitude};
  GPSData position_2 = boat_pos_ - waypoint_1_;

  algebraic_boat_to_line_distance_ =
      (position_1.latitude * position_2.longitude - position_2.latitude * position_1.longitude) * 100000;
}

void CalculationUnit::CheckTackVariable() {
  if (fabsl(algebraic_boat_to_line_distance_) > BOAT_TO_LINE_MAX_DISTANCE / 2) {
    favored_tack_ = Sign(algebraic_boat_to_line_distance_);
  }
}

void CalculationUnit::CalculateAngleOfLine() {
  GPSData waypoint = waypoint_2_ - waypoint_1_;
  angle_of_line_ = atan2(waypoint.latitude, waypoint.longitude);
}

void CalculationUnit::CalculateNominalAngle() {
  nominal_angle_ = angle_of_line_
      - ((2 * INCIDENCE_ANGLE) / M_PI) * atan(algebraic_boat_to_line_distance_ / BOAT_TO_LINE_MAX_DISTANCE);
}

void CalculationUnit::CalculateBoatDirection() {
  // Checks if direction is too close to the wind
  if ((cos(wind_angle_ - nominal_angle_) + cos(CLOSED_HAUL_ANGLE) < 0)
      || (fabsl(algebraic_boat_to_line_distance_) < BOAT_TO_LINE_MAX_DISTANCE
          && (cos(wind_angle_ - angle_of_line_) + cos(CLOSED_HAUL_ANGLE)) < 0)) {
    route_angle_ = M_PI + wind_angle_ - favored_tack_ * CLOSED_HAUL_ANGLE;
  } else {
    // If not, use the previously calculated direction
    route_angle_ = nominal_angle_;
  }
}

void CalculationUnit::CalculateRudderAngle() {
  if (cos(boat_heading_ - route_angle_) >= 0) {
    rudder_angle_ = RUDDER_MAX_ANGLE * sin(boat_heading_ - route_angle_);
  } else {
    rudder_angle_ = RUDDER_MAX_ANGLE * Sign(sin(boat_heading_ - route_angle_));
  }
}

void CalculationUnit::CalculateSailAngle() {
  sail_angle_ = SAIL_MAX_ANGLE * ((cos(wind_angle_ - route_angle_) + 1) / 2);
}

double CalculationUnit::GetRouteAngle() {
  return route_angle_;
}

double CalculationUnit::GetRudderAngle() {
  return rudder_angle_;
}

double CalculationUnit::GetSailAngle() {
  return sail_angle_;
}

double CalculationUnit::Sign(double sign) {
  return (sign > 0) ? 1 : -1;
}

double CalculationUnit::CalculateDistance(const GPSData &position_1, const GPSData &position_2) {
  // Convert to radians
  double distance_latitude = DegreesToRadians(position_2.latitude - position_1.latitude);
  double distance_longitude = DegreesToRadians(position_2.longitude - position_1.longitude);

  double factor =
      sin(distance_latitude / 2) *
          sin(distance_latitude / 2) +
          cos(DegreesToRadians(position_1.latitude)) *
              cos(DegreesToRadians(position_2.latitude)) *
              sin(distance_longitude / 2) *
              sin(distance_longitude / 2);

  double range = 2 * atan2(sqrt(factor), sqrt(1 - factor));
  return range * EARTH_RADIUS * 1000;
}

double CalculationUnit::DegreesToRadians(double degrees) {
  return degrees * (M_PI / 180);
}

int CalculationUnit::NormalizeDegrees(int degrees) {
  while (degrees > 360) degrees -= 360;
  while (degrees < 0) degrees += 360;
  return degrees;
}

double CalculationUnit::ConvertCoordinates(double from_low,
                                           double from_high,
                                           double to_low,
                                           double to_high,
                                           double position) {
  double percentile = (position - from_low) / (from_high - from_low);
  return percentile * (to_high - to_low) + to_low;
}

void CalculationUnit::Report() {
  std::cout << "Servo rudder angle      : " << rudder_angle_ << std::endl;
  std::cout << "Servo sail angle        : " << sail_angle_ << std::endl;
}
