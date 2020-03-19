#include <iostream>
#include <thread>
#include <chrono>
#include "include/DataContainers/gps_position.h"
#include "include/utilities.h"
#include "include/module_cmps12.h"
#include "include/module_gps.h"
#include "include/module_wind_sensor.h"
#include "include/control_unit.h"
#include "include/calculation_unit.h"
#include "include/module_servo.h"
#include "include/logger.h"
#include "test/doctest.h"

#define RUDDER_CHANNEL 1
#define SAIL_CHANNEL 0
#define RUDDER_LOWER_THRESHOLD -1
#define RUDDER_UPPER_THRESHOLD 1
#define SAIL_LOWER_THRESHOLD 0
#define SAIL_UPPER_THRESHOLD 1
#define WIND_SENSOR_SPI_CHANNEL 0
#define OFFSET 90

//Multithreaded for polling devices at different time-intervals
//Thread for driving rudder
void DriveRudder(ModuleServo &rudder) {
  std::cout << "Starting Automatic Rudder Servo" << std::endl;
  while (true) {
    rudder.Run();
  }
}

//Thread for driving sail
void DriveSail(ModuleServo &sail) {
  std::cout << "Starting Automatic Sail Servo" << std::endl;
  while (true) {
    sail.Run();
  }
}

//Thread for polling wind sensor
void PollWindSensor(ModuleWindSensor &wind) {
  std::cout << "Starting Automatic Wind Sensor" << std::endl;
  while (true) {
    //std::cout << "Polling Wind Sensor!" << std::endl;
    wind.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

//Thread for polling gps
void PollGpsSensor(ModuleGPS &gps) {
  std::cout << "Starting Automatic GPS" << std::endl;
  while (true) {
    //std::cout << "Polling GPS!" << std::endl;
    gps.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));
  }
}

//Thread for polling compass
void PollCompass(ModuleCMPS12 &compass) {
  std::cout << "Starting Automatic ModuleCMPS12" << std::endl;
  while (true) {
    //std::cout << "Polling ModuleCMPS12!" << std::endl;
    compass.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

//thread for logging competition data at regular intervals
void LogData(Logger &data_logger) {
  std::cout << "Starting Automatic Logger" << std::endl;
  //Wait for initial time so we have time to do all setup beforehand
  std::this_thread::sleep_for(std::chrono::milliseconds(6000));
  while (true) {
    //std::cout << "Logging Data!" << std::endl;
    data_logger.Publish();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  }
}

int main(int argc, char *argv[]) {
  doctest::Context context(argc, argv);
  int result = context.run();
  if(context.shouldExit()) return result;
  //--------------------------------

  //#These will help us determine where we go
  ControlUnit control_unit;
  CalculationUnit calculation_unit;

  //#These will control our boat
  ModuleServo servo_rudder(
      RUDDER_LOWER_THRESHOLD,
      RUDDER_UPPER_THRESHOLD,
      RUDDER_CHANNEL);

  ModuleServo servo_sail(
      SAIL_LOWER_THRESHOLD,
      SAIL_UPPER_THRESHOLD,
      SAIL_CHANNEL);

  //#These will poll data for us
  ModuleGPS module_gps;
  ModuleCMPS12 module_compass;
  ModuleWindSensor module_wind(WIND_SENSOR_SPI_CHANNEL);

  //Data Loggers (One for competition, other for journey debugging)
  Logger data_logger("/home/alarm/.config/sailingBoat/logs/contest.txt");
  Logger debug_logger("/home/alarm/.config/sailingBoat/logs/waypoint.txt");

  //Init All Modules & Servos
  std::vector<bool> init_status;
  int modules = 5;
  //Set all of them to false for safety
  for (int i = 0; i < modules; i++) {
    init_status.push_back(false);
  }

  //NOTE RE-ENABLE ON PI AS IT IS THE ONLY ONE WITH PROPER SPI / I2C CONNECTIONS
  init_status[0] = servo_rudder.Init();
  init_status[1] = servo_sail.Init();
  init_status[2] = module_gps.Init();
  init_status[3] = module_compass.Init();
  init_status[4] = module_wind.Init();

  //Check if all modules were initialized properly
  bool components_initialized = control_unit.ValidateInits(init_status);
  if (components_initialized) {
    //Read our Data files which determine our goals and other details
    std::string destination = "/home/alarm/.config/sailingBoat/settings/destination.txt";
    std::string settings = "/home/alarm/.config/sailingBoat/settings/settings.txt";
    bool final_status = control_unit.Init(destination, settings);
    if (final_status) {
      std::cout << "[ OK ]    : DESTINATION SET" << std::endl;
    } else {
      std::cout << "[ ERROR ] : DESTINATION SET" << std::endl;
      return -1;
    }
  } else {
    std::cout << "Some Components Failed To Initialize" << std::endl;
    return -1;
  }

  //Default our Servos to their Default positions from start
  servo_sail.SetTarget(0.5);
  servo_rudder.SetTarget(0);

  std::cout << "Activating Threads..." << std::endl;
  //IF all modules were initialize properly we launch our threads
  std::thread t1(PollWindSensor, std::ref(module_wind));
  std::thread t2(PollCompass, std::ref(module_compass));
  std::thread t3(PollGpsSensor, std::ref(module_gps));
  std::thread t4(DriveRudder, std::ref(servo_rudder));
  std::thread t5(DriveSail, std::ref(servo_sail));
  std::thread t6(LogData, std::ref(data_logger));

  //Wait for modules to collect initial set of data
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  std::cout << " - Collecting Initial Dataset - " << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));

  //Publish Initial Log of journey
  //INITIAL WAYPOINT (START)
  //INITIAL READINGS
  /*
  //SCHOOL TEMP
  GPSData TEMP_GPS_DATA;
  TEMP_GPS_DATA.SetValid(true);
  TEMP_GPS_DATA.SetLatitude(60.10347832490164);
  TEMP_GPS_DATA.SetLongitude(19.928544759750366);
  TEMP_GPS_DATA.SetSpeed(0);
  TEMP_GPS_DATA.SetTimeValue(5235);
  TEMP_GPS_DATA.SetTimestamp("12:00:00");

  CMPS12Data TEMP_COMPASS_DATA;
  TEMP_COMPASS_DATA.SetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16,122);

  int TEMP_WIND = 5;

  //TEMP WAYPOINT TEST DATA
  GPSPosition TEMP_WAYPOINT;
  TEMP_WAYPOINT.latitude = 60.105879322635616;
  TEMP_WAYPOINT.longitude = 19.926559925079346;
  */
  //control_unit.SetWaypoint(TEMP_WAYPOINT);
  long int entry = 0;

  data_logger.Write(" - - - BEGINNING NEW JOURNEY - - - ");
  debug_logger.Write(" - - - BEGINNING NEW JOURNEY - - - ");

  while (control_unit.IsActive()) {
    std::cout << "INDEX #" << entry << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(600));
    //module_compass.Report();
    //module_gps.Report();
    //module_wind.Report();

    //Take a nap
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    //std::cout << "Primary Loop" << std::endl;
    //std::cout << "------------------" << std::endl;

    //GRAB A SET OF ITERATION DATA AT THIS MOMENT IN TIME
    //GPSData      gps_reading     = TEMP_GPS_DATA;
    //CMPS12Data   compass_reading = TEMP_COMPASS_DATA;
    int wind_reading = 0;

    //GRAB A SET OF ITERATION DATA AT THIS MOMENT IN TIME
    GPSData gps_reading = module_gps.GetReading();
    CMPS12Data compass_reading = module_compass.GetReading();
    //int         wind_reading    = module_wind.GetReading();

    //Set a waypoint if there is none
    //NOTE Replace with DO-WHILE?
    if (!control_unit.IsWaypointSet()) {
      std::cout << "No Waypoint set" << std::endl;

      int wind_bearing = wind_reading;
      GPSPosition
          current_position = Utilities::ExtractPositionFromData(gps_reading); //GRAB FROM GPS AND UTILITIES TO FORMAT
      int time_unit = gps_reading.GetTimeValue(); //GRAB FROM GPS AND REFORMAT

      std::cout << "Wind Bearing Is: " << wind_bearing << std::endl;

      std::cout << "Current Lat: " << current_position.latitude << std::endl;
      std::cout << "Current Lon: " << current_position.longitude << std::endl;

      //Grab our destination from our control unit
      GPSPosition destination = control_unit.GetDestination();
      std::cout << "Destination Lat: " << destination.latitude << std::endl;
      std::cout << "Destination Lon: " << destination.longitude << std::endl;

      //Calulate destination bearing
      double destination_bearing = Utilities::CoordinatesToDegrees(
          current_position.latitude,
          current_position.longitude,
          destination.latitude,
          destination.longitude);

      std::cout << "Destination Bearing: " << destination_bearing << std::endl;

      //Calculate our angle of approach (AOA)
      double AOA = 0.0;
      if (control_unit.GetAngleDirection() == STARBOARD) {
        std::cout << "Heading Starboard" << std::endl;
        AOA = calculation_unit.CalculateAngleOfApproach(destination_bearing, wind_bearing);
        control_unit.AlternateAngle();
      } else if (control_unit.GetAngleDirection() == PORT) {
        std::cout << "Heading Port" << std::endl;
        AOA = Utilities::FlipDegrees(calculation_unit.CalculateAngleOfApproach(destination_bearing, wind_bearing));
        control_unit.AlternateAngle();
      }

      std::cout << "Reccommended AOA IS: " << AOA << std::endl;

      //Calculate our angle to the new waypoint according to the AOA
      double waypoint_angle = Utilities::Normalize(AOA + destination_bearing);

      std::cout << "Waypoint Angle Is: " << waypoint_angle << std::endl;

      //Calculate the distance to our destination
      double destination_distance = calculation_unit.CalculateDistance(current_position, destination);

      std::cout << "Distance to destination is: " << destination_distance * 1000 << " meters" << std::endl;

      //Calculate how far away our waypoint should be
      double waypoint_distance = destination_distance / control_unit.GetDistanceFactor();

      std::cout << "Waypoint Distance is: " << waypoint_distance * 1000 << " meters" << std::endl;
      if (waypoint_distance < control_unit.GetWaypointCreationThreshold()) {
        std::cout << "Threshold Reached, limiting waypoint" << std::endl;
        waypoint_distance = control_unit.GetWaypointCreationThreshold();
        std::cout << "New Distance is: " << waypoint_distance * 1000 << " meters" << std::endl;
      }

      //Generate new waypoint
      GPSPosition
          new_waypoint = calculation_unit.CalculateWaypoint(current_position, waypoint_distance, waypoint_angle);
      std::cout << "Waypoint Lat: " << new_waypoint.latitude << std::endl;
      std::cout << "Waypoint Lon: " << new_waypoint.longitude << std::endl;

      //Set the waypoint
      control_unit.SetWaypoint(new_waypoint);

      //Set our time unit for our timeout
      control_unit.SetTimeValue(time_unit);

      //Register Status in Journey Log
      //TODO REGISTER
      debug_logger.PublishWaypoint(gps_reading, new_waypoint, "[NEW WAYPOINT SET]");
      std::cout << "Waypoint set" << std::endl;
    }

    //TEST 1 (WAYPOINT GUIDANCE)

    //General CONTROL SECTION
    int compass_bearing = compass_reading.GetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16);
    int wind_bearing = wind_reading;

    std::cout << "Wind Bearing IS: " << wind_bearing << std::endl;
    std::cout << "Boat Bearing Is: " << compass_bearing << std::endl;

    //Grab our current position and waypoint details
    GPSPosition current_position = Utilities::ExtractPositionFromData(gps_reading);
    GPSPosition waypoint_position = control_unit.GetWaypoint();

    std::cout << "Current Lat: " << current_position.latitude << std::endl;
    std::cout << "Current Lon: " << current_position.longitude << std::endl;

    std::cout << "Waypoint Lat: " << waypoint_position.latitude << std::endl;
    std::cout << "Waypoint Lon: " << waypoint_position.longitude << std::endl;

    //Get Bearing to waypoint
    double waypoint_bearing = Utilities::CoordinatesToDegrees(
        current_position.latitude,
        current_position.longitude,
        waypoint_position.latitude,
        waypoint_position.longitude);

    std::cout << "Waypoint Bearing: " << waypoint_bearing << std::endl;

    //Calculate the directional offset of our waypoint
    int waypoint_offset = waypoint_bearing - compass_bearing;
    int wind_offset = compass_bearing - wind_bearing;

    std::cout << "!! Waypoint Offset: " << waypoint_offset << std::endl;
    std::cout << "!! Wind offset: " << wind_offset << std::endl;

    //Generate Vectors to use in our calculation of positions (NOTE THE OFFSET IS 90)
    Vec2 rudder_vector = Utilities::DegreesToVector(waypoint_offset + OFFSET);
    Vec2 sail_vector = Utilities::DegreesToVector(wind_offset + OFFSET);

    //Calculate our settings
    double rudder_setting = calculation_unit.CalculateRudderPosition(rudder_vector);
    double sail_setting = calculation_unit.CalculateSailPosition(sail_vector);

    std::cout << "Rudder Settings: " << rudder_setting << std::endl;
    std::cout << "Sail   Settings: " << sail_setting << std::endl;

    //Set our servos with our calculated targets
    servo_rudder.SetTarget(rudder_setting);
    servo_sail.SetTarget(sail_setting);

    //DESTINATION CALCULATIONS
    double waypoint_distance = calculation_unit.CalculateDistance(current_position, waypoint_position);
    double goal_threshold = control_unit.GetCalculatedThreshold();
    std::cout << "We are " << waypoint_distance * 1000 << " meters from our waypoint" << std::endl;

    std::cout << "DISTANCE THRESHOLD: " << goal_threshold << std::endl;
    std::cout << "WAYPOINT DISTANCE : " << waypoint_distance << std::endl;

    //HAVE WE GOTTEN CLOSE ENOUGH TO OUR WAYPOINT
    if (waypoint_distance < control_unit.GetCalculatedThreshold()) {
      std::cout << "We Are close enough to our destination, grab a new waypoint" << std::endl;
      control_unit.SetWaypointStatus(false);
      //TODO Log EVENT
      GPSPosition ph;
      debug_logger.PublishWaypoint(gps_reading, ph, "[REACHED WAYPOINT, GRAB NEW ONE!]");
      //Set our message in our custom logger to be "Waypoint Reached"
    }

    //Grab our goal (Checkpoint)
    GPSPosition checkpoint = control_unit.GetDestination();
    std::cout << "Checkpoint Lat: " << checkpoint.latitude << std::endl;
    std::cout << "Checkpoint Lon: " << checkpoint.longitude << std::endl;

    //Check how close we are to our Checkpoint(Goal)
    double checkpoint_distance = calculation_unit.CalculateDistance(current_position, checkpoint);
    std::cout << "Distance to Checkpoint: " << checkpoint_distance * 1000 << " meters" << std::endl;
    std::cout << "DISTANCE THRESHOLD: " << goal_threshold * 1000 << " meters" << std::endl;

    //HAVE WE GOTTEN CLOSE ENOUGH TO THE CHECKPOINT
    if (checkpoint_distance < goal_threshold) {
      std::cout << "CHECKPOINT REACHED" << std::endl;
      //Pops the top checkpoint off and turns itself off if at end.
      //TODO Log EVENT
      GPSPosition ph;
      debug_logger.PublishWaypoint(gps_reading, ph, "[CHECKPOINT REACHED]");
      control_unit.UpdateJourney();
      debug_logger.PublishWaypoint(gps_reading, control_unit.GetDestination(), "[NEXT DESTINATION]");
    } else {
      //HAS TOO MUCH TIME PASSED SINCE WE ESTABLISHED THE WAYPOINT
      int gps_time = gps_reading.GetTimeValue();
      std::cout << "GPS TIME: " << gps_time << std::endl;
      if (control_unit.TimeDiscrepencyReached(gps_time)) {
        std::cout << "TOO MUCH TIME HAS PASSED!" << std::endl;
        //Set flag to false to generate new waypoint
        GPSPosition ph;
        debug_logger.PublishWaypoint(gps_reading, ph, "[Too much time has passed to reach waypoint]");
        control_unit.SetWaypointStatus(false);
      }
    }

    //GENERATE Log
    Log fresh_log;
    fresh_log.entry_id = entry;
    fresh_log.bearing = compass_bearing;
    fresh_log.latitude = gps_reading.GetLatitude();
    fresh_log.longitude = gps_reading.GetLongitude();
    fresh_log.speed = gps_reading.GetSpeed();
    fresh_log.timestamp = gps_reading.GetTime();
    fresh_log.distance_from_waypoint = waypoint_distance;
    fresh_log.distance_from_destination = checkpoint_distance;
    data_logger.LogData(fresh_log);

    entry++;
    std::cout << " -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- " << std::endl;
  }

  servo_sail.SetTarget(0.1);
  servo_rudder.SetTarget(0);
  std::cout << "JOURNEY DONE!" << std::endl;

  return result + 0;
}
