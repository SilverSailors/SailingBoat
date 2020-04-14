#include <thread>
#include <chrono>
#include "include/module_cmps12.h"
#include "include/module_gps.h"
#include "include/module_wind.h"
#include "include/control_unit.h"
#include "include/calculation_unit.h"
#include "include/module_servo.h"
#include "include/logger.h"
#include <iostream>
#include "test/doctest.h"
#define RUDDER_CHANNEL 1
#define SAIL_CHANNEL 0
#define RUDDER_LOWER_THRESHOLD -1
#define RUDDER_UPPER_THRESHOLD 1
#define SAIL_LOWER_THRESHOLD 0
#define SAIL_UPPER_THRESHOLD 1
#define CALCULATED_THRESHOLD 5.0 / 2.0

void DriveRudder(ModuleServo &rudder) {
  while (true) {
    rudder.Run();
  }
}

void DriveSail(ModuleServo &sail) {
  while (true) {
    sail.Run();
  }
}

void PollGPS(ModuleGPS &gps) {
  while (true) {
    gps.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
  }
}

void PollCompass(ModuleCMPS12 &compass) {
  while (true) {
    compass.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void PollWind(ModuleWind &wind) {
  while (true) {
    wind.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(60000));
  }
}

void LogData(Logger &data_logger) {
  std::this_thread::sleep_for(std::chrono::milliseconds(6000));
  while (true) {
    data_logger.Publish();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  }
}

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
  ControlUnit control_unit("/home/alarm/.config/sailingBoat/settings/destination.txt");

  // Our loggers
  Logger data_logger("/home/alarm/.config/sailingBoat/logs/contest.json");
  Logger debug_logger("/home/alarm/.config/sailingBoat/logs/waypoint.json");

  // Start threads for asynchronous updating
  std::thread t1(PollWind, std::ref(module_wind));
  std::thread t2(PollCompass, std::ref(module_compass));
  std::thread t3(PollGPS, std::ref(module_gps));
  std::thread t4(DriveRudder, std::ref(servo_rudder));
  std::thread t5(DriveSail, std::ref(servo_sail));
  std::thread t6(LogData, std::ref(data_logger));

  // Start rudder setting
  servo_rudder.SetTarget(0);
  // Start sail setting
  servo_sail.SetTarget(0.5);
  // Beginning of line position
  GPSData waypoint1 = {};
  // End of line position
  GPSData waypoint2 = control_unit.GetDestination();
  // Runs until GPS module is online
  while(waypoint1.latitude != 0.0) {waypoint1 = module_gps.GetReading();}

  // Log entry
  int entry = 1;
  // Runs until no more destinations
  while (control_unit.IsActive()) {
    // Waits half a second each loop
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // Current boat position
    GPSData boat_pos = module_gps.GetReading();
    // Wind direction
    double wind_angle = module_wind.GetReading();
    // Boat sailing direction
    double boat_heading = module_compass.GetReading();
    // Updates values for sail calculation
    calculation_unit.SetBoatValues(waypoint1, waypoint2, boat_pos, wind_angle, boat_heading);
    // Calculates new servo targets
    calculation_unit.Calculate();
    // Updates rudder setting
    servo_rudder.SetTarget(calculation_unit.GetRudderAngle());
    // Updates sail setting
    servo_sail.SetTarget(calculation_unit.GetSailAngle());
    // Distance to destination
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
    new_log.timestamp = boat_pos.timestamp;
    data_logger.LogData(new_log);
    entry++;

    // Outputs journey information
    std::cout << "======================================" << std::endl;
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