#ifndef __UTILITIES_HPP__
#define __UTILITIES_HPP__
#include "Data_Containers/VEC2.hpp"
#include "Data_Containers/GPS_POSITION.hpp"
#include "../Hardware/GPS/GPS_data.hpp"

class Utilities {
 public:
  static double degrees_to_radians(double degrees);
  static double radians_to_degrees(double radians);
  static double convert_coordinates(double from_low, double from_high, double to_low, double to_high, double position);
  static VEC2 degrees_to_vector(double value);
  static double vector_to_degrees(VEC2 vector);
  static double coordinates_to_degrees(double lat1, double lon1, double lat2, double lon2);
  static double flip_degrees(double degrees);
  static GPS_POSITION extract_position_from_data(GPS_DATA data);
  static double normalize(double degrees);
};

#endif //__UTILITIES_HPP__
