#include <iostream>
#include <unistd.h>
#include <math.h>
#include "../Utilities/utilities.hpp"
#include "../Utilities/DataContainers/vec2.hpp"
#include "../Modules/ModuleCmps12/module_cmps12.hpp"
#include "../Modules/ModuleServo//module_servo.hpp"
#include "../Modules/ModuleGps/module_gps.hpp"
#include "../Modules/ModuleWindSensor/module_wind_sensor.hpp"
#include "../Modules/CalculationUnit/calculation_unit.hpp"

int main(int argc, char *argv[]) {
  static const int RUDDER = 1;
  static const int SAIL = 0;

  std::cout << "Starting DEMO" << std::endl;

  ModuleCmps12 compass;
  ModuleServo servo_rudder(-1, 1, RUDDER);
  ModuleServo servo_sail(0, 1, SAIL);
  ModuleGps gps;
  ModuleWindSensor wind_sensor(0);

  CalculationUnit CU;

  bool compass_state = compass.Init();
  bool servo_state_rudder = servo_rudder.Init();
  bool servo_state_sail = servo_sail.Init();
  bool gps_state = gps.Init();
  bool wind_sensor_state = wind_sensor.Init();

  if (compass_state) {
    std::cout << "[ OK ] COMPASS  " << std::endl;
  } else {
    std::cout << "[ ERROR ] COMPASS  " << std::endl;
  }

  if (servo_state_rudder) {
    std::cout << "[ OK ] SERVO: RUDDER" << std::endl;
  } else {
    std::cout << "[ ERROR ] SERVO: RUDDER" << std::endl;
  }

  if (servo_state_sail) {
    std::cout << "[ OK ] SERVO: SAIL" << std::endl;
  } else {
    std::cout << "[ ERROR ] SERVO: SAIL" << std::endl;
  }

  if (gps_state) {
    std::cout << "[ OK ] Gps" << std::endl;
  } else {
    std::cout << "[ ERROR ] Gps" << std::endl;
  }

  if (wind_sensor_state) {
    std::cout << "[ OK ] WIND SENSOR" << std::endl;
  } else {
    std::cout << "[ ERROR ] WIND SENSOR" << std::endl;
  }

  std::cout << "--------------" << std::endl;

  /*
  if(compass_state == false || servo_state == false || gps_state == false)
  {
      std::cout << "[ ERROR ] SOME SYSTEMS FAILED TO INITIALIZE" << std::endl;
      return -1;
  }
  else
  {
      std::cout << "[ OK ] ALL SYSTEMS" << std::endl;
  }
  */

  sleep(2);
  std::cout << "- STARTING SYSTEM -" << std::endl;

  const int offset = 90;
  int waypoint = 120;

  //Vec2 waypoint_vec = Utilities::DegreesToVector(waypoint + offset);

  while (true) {
    //sleep(1);
    sleep(1.2);
    gps.Run();
    //compass.Run();
    //wind_sensor.Read();

    gps.Report();
    //compass.Report();
    //wind_sensor.Report();

    /*
    wind_sensor.Read();
    compass.Run();
    //gps.Run();
    //sleep(1);

    int wind_bearing = wind_sensor.GetReading();
    int bearing = compass.GetReading().GetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16);
    std::cout << "ModuleCmps12 Bearing: " << bearing << std::endl;
    std::cout << "Wind Bearing: " << wind_bearing << std::endl;

    int offset_bearing = bearing + offset;

    Vec2 current_pos = Utilities::degrees_to_vector(offset_bearing);

    //std::cout << "CURRENT X : " << current_pos.x << std::endl;
    //std::cout << "CURRENT Y : " << current_pos.y << std::endl;
    //std::cout << "------------" << std::endl;
    //std::cout << "WAYPOINT X : " << waypoint_vec.x << std::endl;
    //std::cout << "WAYPOINT Y : " << waypoint_vec.y << std::endl;

    //GET OFFSET FOR OUR DESTINATION BEARING
    int dest_offset = waypoint - bearing;

    std::cout << "DESTINATION BEARING: " << dest_offset << std::endl;

    //Rotate it 90 degrees so that Y+1 = NORTH otherwise X+1 IS NORTH
    Vec2 dest = Utilities::degrees_to_vector(dest_offset + 90);
    Vec2 wind = Utilities::DegreesToVector(wind_bearing + 90);

    //std::cout << "DEST X : " << dest.x << std::endl;
    //std::cout << "DEST Y : " << dest.y << std::endl;

    double rudder_setting = CU.CalculateRudderPosition(dest);
    double sail_setting = CU.CalculateSailPosition(wind);

    //std::cout << "RUDDER:: " << rudder_setting << std::endl;
    //std::cout << "SAILS:: " << sail_setting << std::endl;
    servo_rudder.set_target(rudder_setting);
    servo_sail.SetTarget(sail_setting);
    servo_rudder.Run();
    servo_sail.Run();

    double angle_of_approach = CU.CalculateAngleOfApproach(waypoint,bearing);
    std::cout << "Recommended AOA IS: " << angle_of_approach << std::endl;
    */
  }

  return 0;
}
