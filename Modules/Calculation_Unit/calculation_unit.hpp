#ifndef __CALCULATION_UNIT_HPP__
#define __CALCULATION_UNIT_HPP__
#include "../../Utilities/Data_Containers/VEC2.hpp"
#include "../../Utilities/Data_Containers/GPS_POSITION.hpp"
class Calculation_Unit
{
    private:


    public:
      double        calculate_rudder_position(VEC2 vector);
      double        calculate_sail_position(VEC2 vector);
      double        calculate_angle_of_approach(double destination_bearing, double wind_bearing);
      GPS_POSITION  calculate_waypoint(GPS_POSITION current_position, double distance, double direction);
      double        calculate_distance(GPS_POSITION point_a, GPS_POSITION point_b);
};
#endif//__CALCULATION_UNIT_HPP__
