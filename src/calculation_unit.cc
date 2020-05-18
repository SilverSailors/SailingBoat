#include "../include/calculation_unit.h"
#define _USE_MATH_DEFINES
#include <iostream>
constexpr int EARTH_RADIUS = 6371000;
constexpr double BOAT_TO_LINE_MAX_DISTANCE = 25;
constexpr double INCIDENCE_ANGLE = M_PI / 4;
constexpr double CLOSED_HAULED_ANGLE = M_PI / 3;

CalculationUnit::CalculationUnit(int rudder_upper_threshold, int sail_upper_threshold) {
  rudder_max_angle_ = rudder_upper_threshold;
  sail_max_angle_ = sail_upper_threshold;
}

void CalculationUnit::Controller(const GPSData &set_waypoint_1,
                                 const GPSData &set_waypoint_2,
                                 const GPSData &set_boat_pos,
                                 int set_wind_angle,
                                 int set_boat_heading) {
  glm::dvec3
      waypoint_1 =
      GPSToCartesian({DegreesToRadians(set_waypoint_1.latitude), DegreesToRadians(set_waypoint_1.longitude)});
  glm::dvec3
      waypoint_2 =
      GPSToCartesian({DegreesToRadians(set_waypoint_2.latitude), DegreesToRadians(set_waypoint_2.longitude)});
  GPSData boat_pos = {DegreesToRadians(set_boat_pos.latitude), DegreesToRadians(set_boat_pos.longitude)};
  double wind_angle = DegreesToRadians(NormalizeDegrees(set_wind_angle + 180));
  double boat_heading = DegreesToRadians(set_boat_heading);

  // Calculate distance from boat to line
  glm::dvec3 norm = glm::cross(waypoint_1, waypoint_2) / (glm::length(waypoint_1) * glm::length(waypoint_2));
  double boat_to_line_distance = glm::dot(GPSToCartesian(boat_pos), norm);
  std::cout << "boat_to_line_distance: " << boat_to_line_distance << std::endl;

  // Calculate tack variable
  if (favored_tack_ == 0) {
    favored_tack_ = Sign(boat_to_line_distance);
  } else if (fabsl(boat_to_line_distance) > BOAT_TO_LINE_MAX_DISTANCE / 2) {
    favored_tack_ = Sign(boat_to_line_distance);
  }
  std::cout << "favored_tack_: " << favored_tack_ << std::endl;

  // Calculate angle of line
  glm::mat3x2 matrix;
  matrix[0][0] = -sin(boat_pos.longitude);
  matrix[1][0] = cos(boat_pos.longitude);
  matrix[2][0] = 0;
  matrix[0][1] = -cos(boat_pos.longitude) * sin(boat_pos.latitude);
  matrix[1][1] = -sin(boat_pos.latitude) * sin(boat_pos.longitude);
  matrix[2][1] = cos(boat_pos.latitude);

  glm::dvec2 waypoint = matrix * (waypoint_2 - waypoint_1);
  double angle_of_line = atan2(waypoint.x, waypoint.y);
  std::cout << "angle_of_line: " << angle_of_line << std::endl;

  // Calculate nominal angle
  double nominal_angle = angle_of_line
      - 2 * INCIDENCE_ANGLE / M_PI * atan(boat_to_line_distance / BOAT_TO_LINE_MAX_DISTANCE);
  std::cout << "nominal_angle: " << nominal_angle << std::endl;

  // Calculate route angle
  double route_angle;
  // Checks if direction is too close to the wind
  if ((cos(wind_angle - nominal_angle) + cos(CLOSED_HAULED_ANGLE) < 0)
      || (fabsl(boat_to_line_distance) < BOAT_TO_LINE_MAX_DISTANCE
          && (cos(wind_angle - angle_of_line) + cos(CLOSED_HAULED_ANGLE)) < 0)) {
    route_angle = M_PI + wind_angle - favored_tack_ * CLOSED_HAULED_ANGLE;
    std::cout << "DIRECTION IS TOO CLOSE TO THE WIND" << std::endl;
  } else {
    // If not, use the previously calculated direction
    route_angle = nominal_angle;
  }
  std::cout << "route_angle: " << route_angle << std::endl;

  // Calculate rudder and sail angles
  if (cos(boat_heading - route_angle) >= 0) {
    rudder_angle_ = rudder_max_angle_ * sin(boat_heading - route_angle);
  } else {
    rudder_angle_ = rudder_max_angle_ * Sign(sin(boat_heading - route_angle));
  }
  sail_angle_ = sail_max_angle_ * ((cos(wind_angle - route_angle) + 1) / 2);
  std::cout << "rudder angle: " << rudder_angle_ << std::endl;
  std::cout << "sail angle: " << sail_angle_ << std::endl;
}

double CalculationUnit::GetRudderAngle() {
  return rudder_angle_;
}

double CalculationUnit::GetSailAngle() {
  return sail_angle_;
}

double CalculationUnit::DegreesToRadians(double degrees) {
  return degrees * (M_PI / 180);
}

glm::dvec3 CalculationUnit::GPSToCartesian(const GPSData &waypoint) {
  return glm::dvec3(EARTH_RADIUS * cos(waypoint.latitude) * cos(waypoint.longitude),
                    EARTH_RADIUS * cos(waypoint.latitude) * sin(waypoint.longitude),
                    EARTH_RADIUS * sin(waypoint.latitude));
}

int CalculationUnit::NormalizeDegrees(int degrees) {
  while (degrees > 360) degrees -= 360;
  while (degrees < 0) degrees += 360;
  return degrees;
}

int CalculationUnit::Sign(double sign) {
  return (sign > 0) ? 1 : -1;
}

double CalculationUnit::ConvertCoordinates(double from_low,
                                           double from_high,
                                           double to_low,
                                           double to_high,
                                           double position) {
  double percentile = (position - from_low) / (from_high - from_low);
  return percentile * (to_high - to_low) + to_low;
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
  return range * EARTH_RADIUS;
}
