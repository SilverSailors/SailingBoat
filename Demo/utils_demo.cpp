#include <iostream>
#include "../Utilities/utilities.hpp"
#include "../Modules/CalculationUnit/calculation_unit.hpp"
#include <iomanip>
#include <vector>

int main(void) {
  //SCHOOL
  double lat_default = 60.10347832490164;
  double lon_default = 19.928544759750366;

  //WEST (OCEAN COASTLINE)
  double lat_w = 60.10354365796281;
  double lon_w = 19.927384886330515;

  //MUSEUM
  double lat_e = 60.103515315640564;
  double lon_e = 19.93024519376206;

  //CAR DEALER
  double lat_n = 60.10416745166214;
  double lon_n = 19.928647670465693;

  //ALAND SEA ACADEMY
  double lat_s = 60.10302680666239;
  double lon_s = 19.92855754798086;

  double result = 0;

  result = Utilities::CoordinatesToDegrees(lat_default, lon_default, lat_n, lon_n);
  std::cout << "DEGREES NORTH: " << result << std::endl;

  result = Utilities::CoordinatesToDegrees(lat_default, lon_default, lat_e, lon_e);
  std::cout << "DEGREES EAST: " << result << std::endl;

  result = Utilities::CoordinatesToDegrees(lat_default, lon_default, lat_s, lon_s);
  std::cout << "DEGREES SOUTH: " << result << std::endl;

  result = Utilities::CoordinatesToDegrees(lat_default, lon_default, lat_w, lon_w);
  std::cout << "DEGREES WEST: " << result << std::endl;

  /*
  result = Utilities::coordinates_to_degrees(lat_default,lon_default,lat_n,lon_n);
  std::cout << "DEGREES NORTH: " << result << std::endl;

  result = Utilities::coordinates_to_degrees(lat_default,lon_default,lat_e,lon_e);
  std::cout << "DEGREES EAST: " << result << std::endl;

   result = Utilities::coordinates_to_degrees(lat_default,lon_default,lat_s,lon_s);
  std::cout << "DEGREES SOUTH: " << result << std::endl;

  result = Utilities::coordinates_to_degrees(lat_s,lon_s,lat_default,lon_default);
 std::cout << "DEGREES SOUTH INVERSE: " << result << std::endl;

  result = Utilities::CoordinatesToDegrees(lat_default,lon_default,lat_w,lon_w);
  std::cout << "DEGREES WEST: " << result << std::endl;
  */
  std::cout << "-----------" << std::endl;

  /*
  double sail = 0;
  double sailPos = 0.0;
  sailPos = Utilities::ConvertCoordinates(-1,1,0,1,sail);
  std::cout << "Old target is at: " << sail << std::endl;
  std::cout << "New Target is at: " << sailPos << std::endl;

  std::cout << "-----------" << std::endl;
  */
  std::cout << "BOATSIM" << std::endl;

  CalculationUnit CU;

  double distance_factor = 4.0;
  double wind_bearing = 49;

  //double start_lat = 60.10347832490164;
  //double start_lon = 19.928544759750366;

  double start_lat = 60.10577463940261822;
  double start_lon = 19.926656185728546689;

  double destination_lat = 60.105879322635616;
  double destination_lon = 19.926559925079346;

  //SCHOOL
  GpsPosition start;
  start.latitude = start_lat;
  start.longitude = start_lon;

  //AUTO REPAIR SHOP
  GpsPosition destination;
  destination.latitude = destination_lat;
  destination.longitude = destination_lon;

  //FIRST LOOP
  GpsPosition current_position = start;

  //Get bearing to goal
  double destination_bearing = Utilities::CoordinatesToDegrees(
      start.latitude, start.longitude,
      destination.latitude, destination.longitude);

  std::cout << "Destination Bearing is at: " << destination_bearing << std::endl;
  std::cout << "Wind Bearing is at : " << wind_bearing << std::endl;
  //Get our two possible angles
  //double AOA = CU.CalculateAngleOfApproach(destination_bearing,wind_bearing);
  double AOA = Utilities::FlipDegrees(CU.CalculateAngleOfApproach(destination_bearing, wind_bearing));
  std::cout << "AOA (R) : " << AOA << std::endl;
  std::cout << "AOA (L) : " << Utilities::FlipDegrees(AOA) << std::endl;

  //Add our current angle to the recommended one, Normalize
  double waypoint_angle = Utilities::Normalize(AOA + destination_bearing);
  std::cout << "Waypoint Angle Is: " << waypoint_angle << std::endl;

  //Get distance to goal
  double goal_distance = CU.CalculateDistance(current_position, destination);
  double waypoint_distance = goal_distance / distance_factor;
  std::cout << "Distance to goal is: " << goal_distance << std::endl;
  std::cout << "Distance to Waypoint is: " << waypoint_distance << std::endl;

  GpsPosition waypoint = CU.CalculateWaypoint(current_position, waypoint_distance, waypoint_angle);

  std::cout << "WAYPOINT: " << std::setprecision(20) << waypoint.latitude << "," << waypoint.longitude << std::endl;

  /*
  for(int i = 0; i < 360; i++)
  {
    double flipped = Utilities::FlipDegrees(i);
    std::cout << "FLIP: "<<  i << " TO " << flipped << std::endl;
  }
  */

  /*
  //School Coords
  double start_lat = 60.10347832490164;
  double start_lon = 19.928544759750366;

  CalculationUnit CU;
  //SCHOOL
  GpsPosition location;
  location.latitude = start_lat;
  location.longitude = start_lon;

  std::cout << "START VALUES" << std::endl;
  std::cout << "LAT: " << location.latitude << std::endl;
  std::cout << "LON: " << location.longitude << std::endl;
  std::cout << "-----------" << std::endl;
  // 0.2km = 200m
  double distance_kilometers = 0.2;

  GpsPosition place = CU.CalculateWaypoint(location,distance_kilometers,90);
  std::cout << "LAT: " << std::setprecision(1) << place.latitude << std::endl;
  std::cout << "LON: " << std::setprecision(1) << place.longitude << std::endl;

  double distance = CU.CalculateDistance(location,place);

  std::cout << "DISTANCE FROM A -> B :" << distance << std::endl;
  */
  /*
  for(int i = 0; i < 360; i++)
  {
    GpsPosition place = CU.CalculateWaypoint(location,distance_kilometers,i);
    double distance = CU.CalculateDistance(location,place);
    std::cout << "DISTANCE FROM A -> B :" << distance << std::endl;
  }
  */
  return 0;
}
