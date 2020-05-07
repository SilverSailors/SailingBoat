#include "../include/calculation_unit.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
constexpr double EARTH_RADIUS = 6371.0;
constexpr int BOAT_TO_LINE_MAX_DISTANCE = 50;
constexpr int RUDDER_MAX_ANGLE = 1;
constexpr int SAIL_MAX_ANGLE = 1;
constexpr double INCIDENCE_ANGLE = M_PI / 4;
constexpr double CLOSED_HAUL_ANGLE = M_PI / 3;

CalculationUnit::CalculationUnit() {
  algebraic_boat_to_line_distance_ = 0;
  boat_to_line_distance_ = 0;
  favored_tack_ = 0;
  angle_of_line_ = 0;
  nominal_angle_ = 0;
}

void CalculationUnit::SetBoatValues(GPSData waypoint_1,
                                    GPSData waypoint_2,
                                    GPSData boat_pos,
                                    int wind_angle,
                                    int boat_heading) {
  waypoint_1_ = waypoint_1;
  waypoint_2_ = waypoint_2;
  boat_pos_ = boat_pos;
  wind_angle_ = wind_angle;
  boat_heading_ = boat_heading;
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
  GPSData position_1;
  // Calculate unit vector waypoint2 - waypoint1
  position_1 = waypoint_2_ - waypoint_1_;

  double dotproduct_1 = (waypoint_2_.latitude * waypoint_1_.latitude) + (waypoint_2_.longitude * waypoint_1_.longitude);
  double magnitude_1 = sqrt(fabsl(dotproduct_1));

  position_1.latitude = position_1.latitude / magnitude_1;
  position_1.longitude = position_1.longitude / magnitude_1;

  GPSData position_2 = boat_pos_ - waypoint_1_;

  // In the formula, the determinant between two vectors is defined by: det(u,v) = u1v2 - v1u2
  algebraic_boat_to_line_distance_ = (position_1.latitude * position_2.longitude) - (position_2.latitude * position_1.longitude);

  double dotproduct_2 = (position_1.latitude * position_2.latitude) + (position_2.longitude * position_1.longitude);
  double magnitude_2 = sqrt(fabsl(dotproduct_2));

  GPSData closest_point;
  double dist = dotproduct_2 / magnitude_2;
  if (dist < 0 || position_2.latitude == 0) {
    closest_point = waypoint_1_;
  } else if (dist > 1) {
    closest_point = waypoint_2_;
  } else {
    GPSData temp;
    temp.latitude = position_1.latitude * dist;
    temp.longitude = position_1.longitude * dist;

    closest_point.latitude = waypoint_1_.latitude + temp.latitude;
    closest_point.longitude = waypoint_1_.longitude + temp.longitude;
  }
  boat_to_line_distance_ = CalculateDistance(boat_pos_, closest_point);
}

void CalculationUnit::CheckTackVariable() {
  favored_tack_ = Sign(algebraic_boat_to_line_distance_);
}

void CalculationUnit::CalculateAngleOfLine() {
  GPSData position = waypoint_2_ - waypoint_1_;
  angle_of_line_ = RadiansToDegrees(atan2(position.longitude, position.latitude));
}

void CalculationUnit::CalculateNominalAngle() {
  nominal_angle_ = angle_of_line_
      - (((2 * INCIDENCE_ANGLE) / M_PI) * RadiansToDegrees(atan(boat_to_line_distance_ / BOAT_TO_LINE_MAX_DISTANCE)));
}

void CalculationUnit::CalculateBoatDirection() {
  // Checks if direction is too close to the wind
  if ((cos(wind_angle_ - nominal_angle_) + cos(CLOSED_HAUL_ANGLE) < 0)
      || (boat_to_line_distance_ < BOAT_TO_LINE_MAX_DISTANCE
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
  sail_angle_ = 1 - SAIL_MAX_ANGLE * ((cos(wind_angle_ - route_angle_) + 1) / 2);
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
  if (sign < 0) return -1;
  if (sign > 0) return 1;
  return 0;
}

double CalculationUnit::CalculateDistance(GPSData position_1, GPSData position_2) {
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

double CalculationUnit::RadiansToDegrees(double radians) {
  return radians * 180 / M_PI;
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
