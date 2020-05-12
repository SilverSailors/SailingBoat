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
  wind_angle_ = DegreesToRadians(NormalizeDegrees(wind_angle+180-90));
  boat_heading_ = DegreesToRadians(NormalizeDegrees(boat_heading-90));
  std::cout << "wind_angle_: " << wind_angle_ << std::endl;
  std::cout << "boat_heading_: " << boat_heading_ << std::endl;
}

void CalculationUnit::Calculate() {
  std::cout << "----------------" << std::endl;
  CalculateDistanceFromBoatToLine();
  CheckTackVariable();
  CalculateAngleOfLine();
  CalculateNominalAngle();
  CalculateBoatDirection();
  CalculateRudderAngle();
  CalculateSailAngle();
  std::cout << "----------------" << std::endl;
}

void CalculationUnit::CalculateDistanceFromBoatToLine() {
  GPSData waypoint = waypoint_2_ - waypoint_1_;
  double magnitude = sqrt(pow(waypoint.latitude, 2) + pow(waypoint.longitude, 2));

  GPSData position_1 = {waypoint.latitude / magnitude, waypoint.longitude / magnitude};
  GPSData position_2 = boat_pos_ - waypoint_1_;

  boat_to_line_distance_ =
      (position_1.latitude * position_2.longitude - position_2.latitude * position_1.longitude) * 100000;
  std::cout << "boat_to_line_distance_: " << boat_to_line_distance_ << std::endl;
}

void CalculationUnit::CheckTackVariable() {
  if (favored_tack_ == 0) {
    favored_tack_ = Sign(boat_to_line_distance_);
  } else if (fabsl(boat_to_line_distance_) > BOAT_TO_LINE_MAX_DISTANCE / 2) {
    favored_tack_ = Sign(boat_to_line_distance_);
  }
  std::cout << "favored_tack_: " << favored_tack_ << std::endl;
}

void CalculationUnit::CalculateAngleOfLine() {
  GPSData waypoint = waypoint_2_ - waypoint_1_;
  angle_of_line_ = atan2(waypoint.latitude, waypoint.longitude);
  std::cout << "angle_of_line_: " << angle_of_line_ << std::endl;
}

void CalculationUnit::CalculateNominalAngle() {
  nominal_angle_ = angle_of_line_
      - ((2 * INCIDENCE_ANGLE) / M_PI) * atan(boat_to_line_distance_ / BOAT_TO_LINE_MAX_DISTANCE);
  std::cout << "nominal_angle_: " << nominal_angle_ << std::endl;
}

void CalculationUnit::CalculateBoatDirection() {
  // Checks if direction is too close to the wind
  if ((cos(wind_angle_ - nominal_angle_) + cos(CLOSED_HAUL_ANGLE) < 0)
      || (fabsl(boat_to_line_distance_) < BOAT_TO_LINE_MAX_DISTANCE
          && (cos(wind_angle_ - angle_of_line_) + cos(CLOSED_HAUL_ANGLE)) < 0)) {
    route_angle_ = M_PI + wind_angle_ - favored_tack_ * CLOSED_HAUL_ANGLE;
    std::cout << "DIRECTION IS TOO CLOSE TO THE WIND" << std::endl;
  } else {
    // If not, use the previously calculated direction
    route_angle_ = nominal_angle_;
  }
  std::cout << "route_angle_: " << route_angle_ << std::endl;
}

void CalculationUnit::CalculateRudderAngle() {
  if (cos(boat_heading_ - route_angle_) >= 0) {
    rudder_angle_ = RUDDER_MAX_ANGLE * sin(boat_heading_ - route_angle_);
  } else {
    rudder_angle_ = RUDDER_MAX_ANGLE * Sign(sin(boat_heading_ - route_angle_));
  }
  std::cout << "rudder_angle_: " << rudder_angle_ << std::endl;
}

void CalculationUnit::CalculateSailAngle() {
  sail_angle_ = SAIL_MAX_ANGLE * ((cos(wind_angle_ - route_angle_) + 1) / 2);
  std::cout << "sail_angle_: " << sail_angle_ << std::endl;
}

double CalculationUnit::GetBoatToLineDistance() {
  return boat_to_line_distance_;
}

double CalculationUnit::GetFavoredTack() {
  return favored_tack_;
}

double CalculationUnit::GetAngleOfLine() {
  return angle_of_line_;
}

double CalculationUnit::GetNominalAngle() {
  return nominal_angle_;
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
  std::cout << "Servo rudder angle      : " << rudder_angle_ << std::endl;
  std::cout << "Servo sail angle        : " << sail_angle_ << std::endl;
}
