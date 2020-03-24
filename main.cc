#include <thread>
#include <chrono>
#include "include/utilities.h"
#include "include/module_cmps12.h"
#include "include/module_gps.h"
#include "include/module_wind.h"
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
#define OFFSET 90

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

void PollWind(ModuleWind &wind) {
  while (true) {
    wind.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(60000));
  }
}

void PollGpsSensor(ModuleGPS &gps) {
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

void LogData(Logger &data_logger) {
  std::this_thread::sleep_for(std::chrono::milliseconds(6000));
  while (true) {
    data_logger.Publish();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  }
}

int main(int argc, char *argv[]) {
  doctest::Context context(argc, argv);
  int result = context.run();
  if(context.shouldExit()) return result;

  ControlUnit control_unit;
  CalculationUnit calculation_unit;
  ModuleServo servo_rudder(RUDDER_LOWER_THRESHOLD, RUDDER_UPPER_THRESHOLD, RUDDER_CHANNEL);
  ModuleServo servo_sail(SAIL_LOWER_THRESHOLD, SAIL_UPPER_THRESHOLD, SAIL_CHANNEL);
  ModuleGPS module_gps;
  ModuleCMPS12 module_compass;
  ModuleWind module_wind;

  Logger data_logger("/home/alarm/.config/sailingBoat/logs/contest.json");
  Logger debug_logger("/home/alarm/.config/sailingBoat/logs/waypoint.json");

  std::vector<bool> init_status;
  int modules = 5;
  for (int i = 0; i < modules; i++) {
    init_status.push_back(false);
  }
  init_status[0] = servo_rudder.Init();
  init_status[1] = servo_sail.Init();
  init_status[2] = module_gps.Init();
  init_status[3] = module_compass.Init();
  init_status[4] = module_wind.Init();

  bool components_initialized = control_unit.ValidateInits(init_status);
  if (components_initialized) {
    std::string destination = "/home/alarm/.config/sailingBoat/settings/destination.txt";
    std::string settings = "/home/alarm/.config/sailingBoat/settings/settings.txt";
    bool final_status = control_unit.Init(destination, settings);
    if (!final_status) {
      return -1;
    }
  } else {
    return -1;
  }

  servo_sail.SetTarget(0.5);
  servo_rudder.SetTarget(0);

  std::thread t1(PollWind, std::ref(module_wind));
  std::thread t2(PollCompass, std::ref(module_compass));
  std::thread t3(PollGpsSensor, std::ref(module_gps));
  std::thread t4(DriveRudder, std::ref(servo_rudder));
  std::thread t5(DriveSail, std::ref(servo_sail));
  std::thread t6(LogData, std::ref(data_logger));

  std::this_thread::sleep_for(std::chrono::milliseconds(5200));

  long int entry = 0;

  while (control_unit.IsActive()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    GPSData gps_reading = module_gps.GetReading();
    CMPS12Data compass_reading = module_compass.GetReading();
    int wind_reading = module_wind.GetWindDegReading();

    if (!control_unit.IsWaypointSet()) {
      int wind_bearing = wind_reading;
      GPSPosition current_position = Utilities::ExtractPositionFromData(gps_reading);
      int time_unit = gps_reading.GetTimeValue();
      GPSPosition destination = control_unit.GetDestination();
      double destination_bearing = Utilities::CoordinatesToDegrees(
          current_position.latitude,
          current_position.longitude,
          destination.latitude,
          destination.longitude);

      double AOA = 0.0;
      if (control_unit.GetAngleDirection() == STARBOARD) {
        AOA = calculation_unit.CalculateAngleOfApproach(destination_bearing, wind_bearing);
        control_unit.AlternateAngle();
      } else if (control_unit.GetAngleDirection() == PORT) {
        AOA = Utilities::FlipDegrees(calculation_unit.CalculateAngleOfApproach(destination_bearing, wind_bearing));
        control_unit.AlternateAngle();
      }

      double waypoint_angle = Utilities::Normalize(AOA + destination_bearing);
      double destination_distance = calculation_unit.CalculateDistance(current_position, destination);
      double waypoint_distance = destination_distance / control_unit.GetDistanceFactor();

      if (waypoint_distance < control_unit.GetWaypointCreationThreshold()) {
        waypoint_distance = control_unit.GetWaypointCreationThreshold();
      }

      GPSPosition new_waypoint = calculation_unit.CalculateWaypoint(current_position, waypoint_distance, waypoint_angle);
      control_unit.SetWaypoint(new_waypoint);
      control_unit.SetTimeValue(time_unit);
      debug_logger.PublishWaypoint(gps_reading, new_waypoint, "[NEW WAYPOINT SET]");
    }

    int compass_bearing = compass_reading.GetEntry(DATA_SET_COMPASS_BEARING_DEGREES_16);
    int wind_bearing = wind_reading;

    GPSPosition current_position = Utilities::ExtractPositionFromData(gps_reading);
    GPSPosition waypoint_position = control_unit.GetWaypoint();
    double waypoint_bearing = Utilities::CoordinatesToDegrees(
        current_position.latitude,
        current_position.longitude,
        waypoint_position.latitude,
        waypoint_position.longitude);

    int waypoint_offset = waypoint_bearing - compass_bearing;
    int wind_offset = compass_bearing - wind_bearing;

    Vec2 rudder_vector = Utilities::DegreesToVector(waypoint_offset + OFFSET);
    Vec2 sail_vector = Utilities::DegreesToVector(wind_offset + OFFSET);
    double rudder_setting = calculation_unit.CalculateRudderPosition(rudder_vector);
    double sail_setting = calculation_unit.CalculateSailPosition(sail_vector);

    servo_rudder.SetTarget(rudder_setting);
    servo_sail.SetTarget(sail_setting);

    double waypoint_distance = calculation_unit.CalculateDistance(current_position, waypoint_position);
    double goal_threshold = control_unit.GetCalculatedThreshold();

    if (waypoint_distance < control_unit.GetCalculatedThreshold()) {
      control_unit.SetWaypointStatus(false);
      GPSPosition ph;
      debug_logger.PublishWaypoint(gps_reading, ph, "[REACHED WAYPOINT, GRAB NEW ONE!]");
    }

    GPSPosition checkpoint = control_unit.GetDestination();
    double checkpoint_distance = calculation_unit.CalculateDistance(current_position, checkpoint);

    if (checkpoint_distance < goal_threshold) {
      GPSPosition ph;
      debug_logger.PublishWaypoint(gps_reading, ph, "[CHECKPOINT REACHED]");
      control_unit.UpdateJourney();
      debug_logger.PublishWaypoint(gps_reading, control_unit.GetDestination(), "[NEXT DESTINATION]");
    } else {
      int gps_time = gps_reading.GetTimeValue();
      if (control_unit.TimeDiscrepencyReached(gps_time)) {
        GPSPosition ph;
        debug_logger.PublishWaypoint(gps_reading, ph, "[Too much time has passed to reach waypoint]");
        control_unit.SetWaypointStatus(false);
      }
    }

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
  }

  servo_sail.SetTarget(0.1);
  servo_rudder.SetTarget(0);

  return result + 0;
}
