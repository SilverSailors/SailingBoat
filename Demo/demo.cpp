#include <iostream>
#include <unistd.h>
#include <math.h>
#include "../Utilities/utilities.hpp"
#include "../Utilities/Data_Containers/VEC2.hpp"
#include "../Modules/Compass/Module_CMPS12.hpp"
#include "../Modules/Servo/Module_SERVO.hpp"
#include "../Modules/GPS/Module_GPS.hpp"
#include "../Modules/Wind_Sensor/Module_Wind_Sensor.hpp"
#include "../Modules/Calculation_Unit/calculation_unit.hpp"

int main(int argc, char *argv[]) {
  static const int RUDDER = 1;
  static const int SAIL = 0;

  std::cout << "Starting DEMO" << std::endl;

  Module_CMPS12 compass;
  Module_SERVO servo_rudder(-1, 1, RUDDER);
  Module_SERVO servo_sail(0, 1, SAIL);
  Module_GPS gps;
  Module_Wind_Sensor wind_sensor(0);

  Calculation_Unit CU;

  bool compass_state = compass.init();
  bool servo_state_rudder = servo_rudder.init();
  bool servo_state_sail = servo_sail.init();
  bool gps_state = gps.init();
  bool wind_sensor_state = wind_sensor.init();

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
    std::cout << "[ OK ] GPS" << std::endl;
  } else {
    std::cout << "[ ERROR ] GPS" << std::endl;
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

  //VEC2 waypoint_vec = Utilities::degrees_to_vector(waypoint + offset);

  while (true) {
    //sleep(1);
    sleep(1.2);
    gps.run();
    //compass.run();
    //wind_sensor.read();

    gps.report();
    //compass.report();
    //wind_sensor.report();

    /*
    wind_sensor.read();
    compass.run();
    //gps.run();
    //sleep(1);

    int wind_bearing = wind_sensor.get_reading();
    int bearing = compass.get_reading().get_entry(DATA_SET_COMPASS_BEARING_DEGREES_16);
    std::cout << "Compass Bearing: " << bearing << std::endl;
    std::cout << "Wind Bearing: " << wind_bearing << std::endl;

    int offset_bearing = bearing + offset;

    VEC2 current_pos = Utilities::degrees_to_vector(offset_bearing);

    //std::cout << "CURRENT X : " << current_pos.x << std::endl;
    //std::cout << "CURRENT Y : " << current_pos.y << std::endl;
    //std::cout << "------------" << std::endl;
    //std::cout << "WAYPOINT X : " << waypoint_vec.x << std::endl;
    //std::cout << "WAYPOINT Y : " << waypoint_vec.y << std::endl;


    //GET OFFSET FOR OUR DESTINATION BEARING
    int dest_offset = waypoint - bearing;

    std::cout << "DESTINATION BEARING: " << dest_offset << std::endl;

    //Rotate it 90 degrees so that Y+1 = NORTH otherwise X+1 IS NORTH
    VEC2 dest = Utilities::degrees_to_vector(dest_offset + 90);
    VEC2 wind = Utilities::degrees_to_vector(wind_bearing + 90);

    //std::cout << "DEST X : " << dest.x << std::endl;
    //std::cout << "DEST Y : " << dest.y << std::endl;

    double rudder_setting = CU.calculate_rudder_position(dest);
    double sail_setting = CU.calculate_sail_position(wind);

    //std::cout << "RUDDER:: " << rudder_setting << std::endl;
    //std::cout << "SAILS:: " << sail_setting << std::endl;
    servo_rudder.set_target(rudder_setting);
    servo_sail.set_target(sail_setting);
    servo_rudder.run();
    servo_sail.run();

    double angle_of_approach = CU.calculate_angle_of_approach(waypoint,bearing);
    std::cout << "Recommended AOA IS: " << angle_of_approach << std::endl;
    */


  }

  return 0;
}
