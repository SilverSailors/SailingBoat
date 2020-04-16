#include "../include/calculation_unit.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265
#define EARTH_RADIUS 6371.0
#define BOAT_TO_LINE_MAX_DISTANCE 50
#define RUDDER_MAX_ANGLE 1
#define SAIL_MAX_ANGLE 1
#define INCIDENCE_ANGLE PI/4
#define CLOSED_HAUL_ANGLE PI/3

CalculationUnit::CalculationUnit() {
  boat_to_line_distance_ = 0;
  favored_tack_ = 0;
  angle_of_line_ = 0;
  nominal_angle_ = 0;
  new_data_available_ = false;
}

void CalculationUnit::SetBoatValues(GPSData waypoint1,
                                    GPSData waypoint2,
                                    GPSData boat_pos,
                                    double wind_angle,
                                    double boat_heading) {
  waypoint1_ = waypoint1;
  waypoint2_ = waypoint2;
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
  new_data_available_ = true;
}

void CalculationUnit::CalculateDistanceFromBoatToLine() {
  GPSData position1;
  // Calculate unit vector waypoint2 - waypoint1
  position1 = waypoint2_ - waypoint1_;

  double dotproduct = (waypoint2_.latitude * waypoint1_.latitude) + (waypoint2_.longitude * waypoint1_.longitude);
  double magnitude = sqrt(dotproduct);

  position1.latitude = position1.latitude / magnitude;
  position1.longitude = position1.longitude / magnitude;

  GPSData position2 = boat_pos_ - waypoint1_;

  // In the formula, the determinant between two vectors is defined by: det(u,v) = u1v2 - v1u2
  boat_to_line_distance_ = (position1.latitude * position2.longitude) - (position2.latitude * position1.longitude);
}

void CalculationUnit::CheckTackVariable() {
  favored_tack_ = Sign(boat_to_line_distance_);
}

void CalculationUnit::CalculateAngleOfLine() {
  GPSData position = waypoint2_ - waypoint1_;
  angle_of_line_ = RadiansToDegrees(atan2(position.longitude, position.latitude));
}

void CalculationUnit::CalculateNominalAngle() {
  nominal_angle_ = angle_of_line_
      - (((2 * INCIDENCE_ANGLE) / PI) * RadiansToDegrees(atan(boat_to_line_distance_ / BOAT_TO_LINE_MAX_DISTANCE)));
}

void CalculationUnit::CalculateBoatDirection() {
  // Checks if direction is too close to the wind
  if ((cos(wind_angle_ - nominal_angle_) + cos(CLOSED_HAUL_ANGLE) < 0)
      || (abs(boat_to_line_distance_) < BOAT_TO_LINE_MAX_DISTANCE
          && (cos(wind_angle_ - angle_of_line_) + cos(CLOSED_HAUL_ANGLE)) < 0)) {
    route_angle_ = PI + wind_angle_ - favored_tack_ * CLOSED_HAUL_ANGLE;
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

double CalculationUnit::CalculateDistance(GPSData position1, GPSData position2) {
  // Convert to radians
  double distance_latitude = DegreesToRadians(position2.latitude - position1.latitude);
  double distance_longitude = DegreesToRadians(position2.longitude - position1.longitude);

  double factor =
      sin(distance_latitude / 2) *
          sin(distance_latitude / 2) +
          cos(DegreesToRadians(position1.latitude)) *
              cos(DegreesToRadians(position2.latitude)) *
              sin(distance_longitude / 2) *
              sin(distance_longitude / 2);

  double range = 2 * atan2(sqrt(factor), sqrt(1 - factor));
  return range * EARTH_RADIUS;
}

double CalculationUnit::DegreesToRadians(double degrees) {
  return degrees * (PI / 180);
}

double CalculationUnit::RadiansToDegrees(double radians) {
  return radians * 180 / PI;
}

double CalculationUnit::NormalizeDegrees(double degrees) {
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
  if (new_data_available_) {
    std::cout << "Servo rudder angle      : " << rudder_angle_ << std::endl;
    std::cout << "Servo sail angle        : " << sail_angle_ << std::endl;
    new_data_available_ = false;
  }
}