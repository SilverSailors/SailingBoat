#include "control_unit.h"
#include <iostream>
#include "../../Core/IO/io.h"
#include "../../Core/Parser/parser.h"

ControlUnit::ControlUnit() {
  active_ = false;
  waypoint_reached_ = false;
  waypoint_set_ = false;
  destination_reached_ = false;
  destination_set_ = false;

  waypoint_.latitude = 0;
  waypoint_.longitude = 0;

  distance_threshold_ = 0;
  time_threshold_ = 0;
  distance_factor_ = 0;
  calculated_threshold_ = 0;
  waypoint_distance_creation_threshold_ = 0;

  angle_direction_ = STARBOARD;
}

bool ControlUnit::Init(std::string destination, std::string settings) {
  IO io;
  Parser parser;

  //Get file data and remove all comments
  std::vector<std::string> data_raw = io.ReadFile(destination);
  std::vector<std::string> data_clean = parser.RemoveComments(data_raw);
  int checkpoints = data_clean.size();
  std::cout << "We Have #" << checkpoints << " Checkpoints to travel to" << std::endl;

  //Store each checkpoints in reverse (FIFO, we want our first one to be on top of the stack)
  for (int i = 0; i < checkpoints; i++) {
    std::vector<std::string> split = parser.SplitString(data_clean[i], ',');
    if (split.size() == 2) {
      GPSPosition pin;
      pin.latitude = std::atof(split[0].c_str());
      pin.longitude = std::atof(split[1].c_str());
      destination_.push(pin);
    } else {
      std::cout << "COORDINATE ERROR" << std::endl;
      active_ = false;
      return false;
    }
  }
  std::cout << "Destination Coordinates Logged" << std::endl;
  destination_set_ = true;

  //Store threshold variables
  std::vector<std::string> settings_raw = io.ReadFile(settings);
  std::vector<std::string> settings_clean = parser.RemoveComments(settings_raw);
  //NOTE THAT OUR ELEMENTS ARE THE SETTINGS POSITIONS; REMOVAL OF SETTINGS OR
  //ADDING WITHOUT MENDING WILL CAUSE FAULTS
  int total_settings = settings_clean.size();
  std::cout << "Total Settings found: " << total_settings << std::endl;
  if (total_settings < 2) {
    std::cout << "SETTINGS FILE CORRUPT / MISSING: DEFAULTING TO STANDARD VALUES (0/0)" << std::endl;
    distance_threshold_ = 0;
    time_threshold_ = 0;
    distance_factor_ = 1.0;
    waypoint_distance_creation_threshold_ = 0;
    calculated_threshold_ = distance_threshold_ / distance_factor_;
  } else {
    //NOTE WE DONT REMOVE EMPTY LINES SO WE SKIP [1] AS IT IS EMPTY
    distance_threshold_ = std::atof(settings_clean[0].c_str());
    time_threshold_ = std::atof(settings_clean[2].c_str());
    distance_factor_ = std::atof(settings_clean[4].c_str());
    waypoint_distance_creation_threshold_ = std::atof(settings_clean[6].c_str()) / 1000;
    calculated_threshold_ = distance_threshold_ / 1000;
  }

  std::cout << "Distance (M) : " << distance_threshold_ << std::endl;
  std::cout << "Time     (S) : " << time_threshold_ << std::endl;
  std::cout << "Factor   (U) : " << distance_factor_ << std::endl;
  std::cout << "Factor   (G) : " << waypoint_distance_creation_threshold_ << std::endl;

  active_ = true;
  return true;
}

bool ControlUnit::IsActive() {
  return active_;
}

GPSPosition ControlUnit::GetDestination() {
  return destination_.front();
}

GPSPosition ControlUnit::GetWaypoint() {
  return waypoint_;
}

double ControlUnit::GetDistanceThreshold() {
  return distance_threshold_;
}

double ControlUnit::GetWaypointCreationThreshold() {
  return waypoint_distance_creation_threshold_;
}

void ControlUnit::UpdateJourney() {
  if (destination_.size() > 0) {
    destination_.pop();
    waypoint_set_ = false;
    waypoint_.latitude = 0;
    waypoint_.longitude = 0;
  } else if (destination_.size() == 0) {
    std::cout << "JOURNEY COMPLETE!" << std::endl;
    //active_ = false;
  }
}

void ControlUnit::SetWaypoint(GPSPosition waypoint) {
  waypoint_.latitude = waypoint.latitude;
  waypoint_.longitude = waypoint.longitude;
  waypoint_set_ = true;
}

bool ControlUnit::ValidateInits(std::vector<bool> statuses) {
  bool result = true;

  if (statuses[0]) {
    std::cout << "[ OK ]    : Servo Rudder" << std::endl;
  } else {
    std::cout << "[ ERROR ] : Servo Rudder" << std::endl;
    result = false;
  }

  if (statuses[1]) {
    std::cout << "[ OK ]    : Servo Sail" << std::endl;
  } else {
    std::cout << "[ ERROR ] : Servo Sail" << std::endl;
    result = false;
  }

  if (statuses[2]) {
    std::cout << "[ OK ]    : Module GPS" << std::endl;
  } else {
    std::cout << "[ ERROR ] : Module GPS" << std::endl;
    result = false;
  }

  if (statuses[3]) {
    std::cout << "[ OK ] : Module ModuleCMPS12" << std::endl;
  } else {
    std::cout << "[ ERROR ] : Module ModuleCMPS12" << std::endl;
    result = false;
  }

  if (statuses[4]) {
    std::cout << "[ OK ] : Module Wind Sensor" << std::endl;
  } else {
    std::cout << "[ ERROR ] : Module Wind Sensor" << std::endl;
    result = false;
  }

  //TEMP
  return true;

  return result;
}

bool ControlUnit::IsWaypointSet() {
  return waypoint_set_;
}

void ControlUnit::AlternateAngle() {
  if (angle_direction_ == STARBOARD) {
    angle_direction_ = PORT;
  } else {
    angle_direction_ = STARBOARD;
  }
}

Angle ControlUnit::GetAngleDirection() {
  return angle_direction_;
}

double ControlUnit::GetDistanceFactor() {
  return distance_factor_;
}

bool ControlUnit::TimeDiscrepencyReached(int time_value) {
  if (time_value - time_value_ >= time_threshold_) {
    std::cout << "TIME LIMIT REACHED" << std::endl;
    return true;
  }
  return false;
}

void ControlUnit::SetTimeValue(int value) {
  time_value_ = value;
}

void ControlUnit::SetWaypointStatus(bool status) {
  waypoint_set_ = status;
}

double ControlUnit::GetCalculatedThreshold() {
  return calculated_threshold_;
}
