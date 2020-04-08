#ifndef SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#define SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
#include "DataContainers/gps_data.h"

class CalculationUnit {
 public:
  /**
   * Constructor, initializes member fields
   */
  CalculationUnit();
  /**
   * Returns if CalculationUnit is initialized
   * @return If initialized
   */
  bool GetInitialized();
  /**
   * Calculates new settings for rudder and sail
   */
  void Calculate();
  /**
   * @param waypoint1 First waypoint
   * @param waypoint2 Second waypoint
   * @param boat_pos Boat position
   * @param wind_angle Wind direction
   * @param boat_heading Boat sail direction
   */
  void SetBoatValues(GPSData waypoint1, GPSData waypoint2, GPSData boat_pos, double wind_angle, double boat_heading);
  /**
   * Calculates distance from boat to line of the two waypoints
   */
  void CalculateDistanceFromBoatToLine();
  /**
   * Sets favored_tack_
   */
  void CheckTackVariable();
  /**
   * Calculates angle between line and east
   */
  void CalculateAngleOfLine();
  /**
   * Nominal angle that the boat has to follow
   */
  void CalculateNominalAngle();
  /**
   * Calculates direction to sail
   */
  void CalculateBoatDirection();
  /**
   * Calculates new rudder setting
   */
  void CalculateRudderAngle();
  /**
   * Calculates new sail setting
   */
  void CalculateSailAngle();
  /**
   * Returns rudder_angle_ member field
   * @return rudder_angle_ value
   */
  double GetRudderAngle();
  /**
   * Returns sail_angle_ member field
   * @return sail_angle_ value
   */
  double GetSailAngle();
  /**
   * Returns value depending on sign value
   * @param sign Sign in form of number
   * @return -1 or +1
   */
  double Sign(double sign);
  /**
   * Calculates the distance between the two positions
   * @param position1 First position
   * @param position2 Second position
   * @return Distance between the positions
   */
  double CalculateDistance(GPSData position1, GPSData position2);
  /**
   * Converts given degrees to radians format
   * @param degrees Degrees value
   * @return Value in radians
   */
  static double DegreesToRadians(double degrees);
  /**
   * Normalizes degrees to between 0 and 360
   * @param degrees Degrees value
   * @return Normalized value
   */
  static double NormalizeDegrees(double degrees);
  /**
   * Converts given from-, to- and position-coordinates to double
   * @param from_low From low
   * @param from_high From high
   * @param to_low To low
   * @param to_high To high
   * @param position Position
   * @return Result from conversion
   */
  static double ConvertCoordinates(double from_low, double from_high,
                            double to_low, double to_high, double position);
 private:
  /**
   * If CalculationUnit is initialized
   */
  bool initialized_;
  /**
   * First waypoint
   */
  GPSData waypoint1_;
  /**
   * Second waypoint
   */
  GPSData waypoint2_;
  /**
   * Current boat position
   */
  GPSData boat_pos_;
  /**
   * Wind direction
   */
  double wind_angle_;
  /**
   * Distance between boat and line
   */
  double boat_to_line_distance_;
  /**
   * Favored tack
   */
  double favored_tack_;
  /**
   * Angle between line and east
   */
  double angle_of_line_;
  /**
   * Nominal angle
   */
  double nominal_angle_;
  /**
   * Preferred sailing direction
   */
  double route_angle_;
  /**
   * Boat sailing direction
   */
  double boat_heading_;
  /**
   * Angle of rudder
   */
  double rudder_angle_;
  /**
   * Angle of sail
   */
  double sail_angle_;
};

#endif // SAILINGBOAT_INCLUDE_CALCULATION_UNIT_H_
