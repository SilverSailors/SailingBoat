#include "calculation_unit.hpp"
#include <math.h>
#include <iostream>
#include "../../Utilities/utilities.hpp"
#define EARTH_RADIUS 6371.0

double CalculationUnit::CalculateRudderPosition(Vec2 vector) {
  //NOTE VECTOR BEARING SHOULD BE ROTATED 90 DEGREES SO THAT X,Y = 0,1 IS NORTH

  //NOTE Dead zone represents how much of our centering we should ignore
  //This is to prevent constant wiggle as we try to center in on our target
  const double RUDDER_DEAD_ZONE = 0.225;

  //V.x = cos(A)
  //V.y = sin(A)

  //If Y is negative then we need to turn around
  if (vector.y <= 0) {
    //TURN RIGHT
    if (vector.x >= 0) {
      //std::cout << "WRONG SIDE : TURN RIGHT " << std::endl;
      return 1;
    }
      //TURN LEFT
    else if (vector.x < 0) {
      //std::cout << "RONG SIDE : TURN LEFT" << std::endl;
      return -1;
    }
  }
    //We are looking in the correct half
  else {
    double threshold = RUDDER_DEAD_ZONE - abs(vector.x);
    //std::cout << "DEADZONE: " << threshold << std::endl;
    if (threshold >= 0) {
      //GO STRAIGHT
      //std::cout << "THRESHOLD REACHED GO STRAIGHT!!" << std::endl;
      return 0;
    } else {
      //TURN RIGHT
      if (vector.x >= 0) {
        //std::cout << "CORRECT SIDE : TURN RIGHT " << std::endl;
        return 0.5;
      }
        //TURN LEFT
      else if (vector.x < 0) {
        //std::cout << "CORRECT SIDE : TURN LEFT" << std::endl;
        return -0.5;
      }
    }
  }

  return 0;
}

double CalculationUnit::CalculateSailPosition(Vec2 vector) {
  //IF Y IS POSITIVE THEN WIND AT OUR BACKS (GOOD)
  //IF Y IS NEGATIVE THEN WIND IS BLOWING AT US (BAD)
  //IF Y IS 0 THEN IT IS FROM OUR SIDE

  //Y AXIS DETERMINES HOW HARD WE NEED TO SWING OUR SAILS
  //-1 MIN
  //+1 MAX

  //ADDING IN RESTRAINT TO SAIL AS WE DONT NEED ALL POWER (TOO WIDE IN LOWER ANGLES, 0-75%)
  double sail = Utilities::ConvertCoordinates(-1, 1, 0, 0.75, vector.y);

  double temp = Utilities::ConvertCoordinates(-1, 1, 0, 1, vector.y);
  double sail_power = sail;
  std::cout << "SAILS ARE AT: " << temp * 100 << " Percentage" << std::endl;
  //POS NEG X IS IRRELEVANT AS SAIL CAN SWING AROUND TO OTHER SIDE
  return sail_power;
}

double CalculationUnit::CalculateAngleOfApproach(double destination_bearing, double wind_bearing) {
  //Even if we are head on we want to move
  //slightly to the side for good measure
  const double upper_angle_discrepancy = 45.0;
  const double lower_angle_discrepancy = 5.0;
  //const double max_angle = 90.0;

  //Calculate single side of our bearings (To get other side just flip)
  double offset = abs(destination_bearing - wind_bearing);
  if (offset > 180) offset = abs(offset - 360);

  //std::cout << "OFFSET: " << offset << std::endl;

  //Cut it in half so that we can only turn +- 90 degrees
  offset = offset / 2;

  //Add our discrepancy;

  //std::cout << "PROPER Angle OFFSET: " << offset << std::endl;

  //If our angle is too big or too small
  //Offset with our discrepancy so we get a small variation
  if (offset < lower_angle_discrepancy) offset = lower_angle_discrepancy;
  if (offset > upper_angle_discrepancy) offset = upper_angle_discrepancy;
  return offset;
}

GpsPosition CalculationUnit::CalculateWaypoint(GpsPosition current_position, double distance, double direction) {
  //STOLEN FROM THE INTERNET (Hence d, c, they did not specifiy what they meant)

  //LATITUDE
  double latitude_radians = Utilities::DegreesToRadians(current_position.latitude);
  double angle_radians = Utilities::DegreesToRadians(direction);
  double d = distance / EARTH_RADIUS;
  double c = asin(sin(latitude_radians) * cos(d) + cos(latitude_radians) * sin(d) * cos(angle_radians));
  double corrected_latitude = Utilities::RadiansToDegrees(c);

  //LONGITUDE
  double c2 = atan2(sin(angle_radians) * sin(d) * cos(latitude_radians), cos(d) - sin(latitude_radians) * sin(c));
  double corrected_longitude = current_position.longitude + Utilities::RadiansToDegrees(c2);

  GpsPosition coords;
  coords.latitude = corrected_latitude;
  coords.longitude = corrected_longitude;
  return coords;
}

double CalculationUnit::CalculateDistance(GpsPosition point_a, GpsPosition point_b) {
  //Convert to radian
  double distance_latitude = Utilities::DegreesToRadians(point_b.latitude - point_a.latitude);
  double distance_longitude = Utilities::DegreesToRadians(point_b.longitude - point_a.longitude);

  double factor =
      sin(distance_latitude / 2) *
          sin(distance_latitude / 2) +
          cos(Utilities::DegreesToRadians(point_a.latitude)) *
              cos(Utilities::DegreesToRadians(point_b.latitude)) *
              sin(distance_longitude / 2) *
              sin(distance_longitude / 2);

  double range = 2 * atan2(sqrt(factor), sqrt(1 - factor));
  double distance = range * EARTH_RADIUS;
  return distance;
}
