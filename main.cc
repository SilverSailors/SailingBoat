#include "include/threads.h"
#include "include/module_servo.h"
#include "include/module_gps.h"
#include "include/module_cmps12.h"
#include "include/module_wind.h"
#include "include/calculation_unit.h"
#include "include/control_unit.h"
#include "include/logger.h"
#include <thread>
#include <chrono>
#include <iostream>
#include "test/doctest.h"
constexpr int RUDDER_CHANNEL = 1;
constexpr int SAIL_CHANNEL = 0;
constexpr int RUDDER_LOWER_THRESHOLD = -1;
constexpr int RUDDER_UPPER_THRESHOLD = 1;
constexpr int SAIL_LOWER_THRESHOLD = 0;
constexpr int SAIL_UPPER_THRESHOLD = 1;
constexpr double CALCULATED_THRESHOLD = 5;

int main(int argc, char *argv[]) {
  // If testing should be done
  doctest::Context context(argc, argv);
  int result = context.run();
  if(context.shouldExit()) return result;

  // Creates and initializes modules
  ModuleServo servo_rudder(RUDDER_LOWER_THRESHOLD, RUDDER_UPPER_THRESHOLD, RUDDER_CHANNEL);
  ModuleServo servo_sail(SAIL_LOWER_THRESHOLD, SAIL_UPPER_THRESHOLD, SAIL_CHANNEL);
  ModuleGPS module_gps;
  ModuleCMPS12 module_compass;
  ModuleWind module_wind;
  CalculationUnit calculation_unit;

  // Checks if all modules are OK
  bool fail = false;
  if (!servo_rudder.GetInitialized()) { std::cout << "Servo rudder not initialized!" << std::endl; fail = true; }
  else if (!servo_sail.GetInitialized()) { std::cout << "Servo sail not initialized!" << std::endl; fail = true; }
  else if (!module_gps.GetInitialized()) { std::cout << "Module GPS not initialized!" << std::endl; fail = true; }
  else if (!module_compass.GetInitialized()) { std::cout << "Module compass not initialized!" << std::endl; fail = true; }
  else if (!module_wind.GetInitialized()) { std::cout << "Module wind not initialized!" << std::endl; fail = true; }
  if (fail) return -1;
  else std::cout << "All modules initialized!" << std::endl;

  // Creates control unit for journey, with destinations path
  ControlUnit control_unit("/home/pi/.config/sailingBoat/settings/destination.txt");

  // Our loggers
  time_t raw_time = std::time(nullptr);
  char timeiso[20];
  strftime(timeiso, sizeof(timeiso), "%Y-%m-%d-%H-%M-%S", localtime(&raw_time));
  Logger data_logger(std::string("/home/pi/.config/sailingBoat/logs/data_") + timeiso + ".json");
  Logger debug_logger(std::string("/home/pi/.config/sailingBoat/logs/debug_") + timeiso + ".json");

  // Start polling threads
  std::thread t1(PollWind, std::ref(module_wind));
  std::thread t2(PollCompass, std::ref(module_compass));
  std::thread t3(PollGPS, std::ref(module_gps));

  // Start rudder and sail settings
  servo_rudder.SetTarget(0);
  servo_sail.SetTarget(0.5);

  // Beginning of line position
  GPSData waypoint1 = {};
  // End of line position
  GPSData waypoint2 = control_unit.GetDestination();

  // Runs until GPS module is online
  while(waypoint1.latitude == 0.0) {
    waypoint1 = module_gps.GetReading();
    std::cout << "GPS not ready yet!" << std::endl;
  }

  // Start the remaining threads
  std::thread t4(DriveRudder, std::ref(servo_rudder));
  std::thread t5(DriveSail, std::ref(servo_sail));
  std::thread t6(LogData, std::ref(data_logger));

  // Log entry id
  int entry = 1;
  // Runs until no more destinations
  while (control_unit.IsActive()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // Get new readings
    GPSData boat_pos = module_gps.GetReading();
    double wind_angle = module_wind.GetReading();
    double boat_heading = module_compass.GetReading();

    // Updates values for sail calculation
    calculation_unit.SetBoatValues(waypoint1, waypoint2, boat_pos, wind_angle, boat_heading);
    // Calculates new servo targets
    calculation_unit.Calculate();

    // Updates rudder and sail settings
    servo_rudder.SetTarget(calculation_unit.GetRudderAngle());
    servo_sail.SetTarget(calculation_unit.GetSailAngle());

    double destination_distance = calculation_unit.CalculateDistance(boat_pos, waypoint2);
    // If close enough to destination
    if (destination_distance < CALCULATED_THRESHOLD) {
      // Get next destination or quit
      control_unit.UpdateJourney();
      // Write debug
      debug_logger.PublishWaypoint(boat_pos, control_unit.GetDestination(), "CHECKPOINT REACHED, NEXT DESTINATION");

      // New beginning of line
      waypoint1 = waypoint2;
      // New end of line position
      waypoint2 = control_unit.GetDestination();
    }

    // Logs an entry
    Log new_log;
    new_log.entry_id = entry;
    new_log.latitude = boat_pos.latitude;
    new_log.longitude = boat_pos.longitude;
    new_log.rudder_angle = calculation_unit.GetRudderAngle();
    new_log.sail_angle = calculation_unit.GetSailAngle();
    new_log.timestamp = boat_pos.timestamp;
    data_logger.LogData(new_log);
    entry++;

    // Outputs journey information
    std::cout << "=============================================" << std::endl;
    module_gps.Report();
    module_wind.Report();
    module_compass.Report();
    calculation_unit.Report();
    std::cout << "Distance to destination : " << destination_distance << std::endl;
  }

  // Destroys the threads created
  t1.detach();
  t2.detach();
  t3.detach();
  t4.detach();
  t5.detach();
  t6.detach();

  return 0;
}
