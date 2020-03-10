#include "control_unit.hpp"
#include <iostream>
#include "../../Core/IO/IO.hpp"
#include "../../Core/Parser/Parser.hpp"

Control_Unit::Control_Unit() {
  m_active = false;
  m_waypoint_reached = false;
  m_waypoint_set = false;
  m_destination_reached = false;
  m_destination_set = false;

  m_waypoint.latitude = 0;
  m_waypoint.longitude = 0;

  m_distance_threshold = 0;
  m_time_threshold = 0;
  m_distance_factor = 0;
  m_calculated_threshold = 0;
  m_waypoint_distance_creation_threshold = 0;

  m_angle_direction = STARBOARD;
}

bool Control_Unit::init(std::string destination, std::string settings) {
  IO io;
  Parser parser;

  //Get file data and remove all comments
  std::vector<std::string> data_raw = io.read_file(destination);
  std::vector<std::string> data_clean = parser.remove_comments(data_raw);
  int checkpoints = data_clean.size();
  std::cout << "We Have #" << checkpoints << " Checkpoints to travel to" << std::endl;

  //Store each checkpoints in reverse (FIFO, we want our first one to be on top of the stack)
  for (int i = 0; i < checkpoints; i++) {
    std::vector<std::string> split = parser.split_string(data_clean[i], ',');
    if (split.size() == 2) {
      GPS_POSITION pin;
      pin.latitude = std::atof(split[0].c_str());
      pin.longitude = std::atof(split[1].c_str());
      m_destination.push(pin);
    } else {
      std::cout << "COORDINATE ERROR" << std::endl;
      m_active = false;
      return false;
    }
  }
  std::cout << "Destination Coordinates Logged" << std::endl;
  m_destination_set = true;

  //Store threshold variables
  std::vector<std::string> settings_raw = io.read_file(settings);
  std::vector<std::string> settings_clean = parser.remove_comments(settings_raw);
  //NOTE THAT OUR ELEMENTS ARE THE SETTINGS POSITIONS; REMOVAL OF SETTINGS OR
  //ADDING WITHOUT MENDING WILL CAUSE FAULTS
  int total_settings = settings_clean.size();
  std::cout << "Total Settings found: " << total_settings << std::endl;
  if (total_settings < 2) {
    std::cout << "SETTINGS FILE CORRUPT / MISSING: DEFAULTING TO STANDARD VALUES (0/0)" << std::endl;
    m_distance_threshold = 0;
    m_time_threshold = 0;
    m_distance_factor = 1.0;
    m_waypoint_distance_creation_threshold = 0;
    m_calculated_threshold = m_distance_threshold / m_distance_factor;
  } else {
    //NOTE WE DONT REMOVE EMPTY LINES SO WE SKIP [1] AS IT IS EMPTY
    m_distance_threshold = std::atof(settings_clean[0].c_str());
    m_time_threshold = std::atof(settings_clean[2].c_str());
    m_distance_factor = std::atof(settings_clean[4].c_str());
    m_waypoint_distance_creation_threshold = std::atof(settings_clean[6].c_str()) / 1000;
    m_calculated_threshold = m_distance_threshold / 1000;
  }

  std::cout << "Distance (M) : " << m_distance_threshold << std::endl;
  std::cout << "Time     (S) : " << m_time_threshold << std::endl;
  std::cout << "Factor   (U) : " << m_distance_factor << std::endl;
  std::cout << "Factor   (G) : " << m_waypoint_distance_creation_threshold << std::endl;

  m_active = true;
  return true;
}

bool Control_Unit::is_active() {
  return m_active;
}

GPS_POSITION Control_Unit::get_destination() {
  return m_destination.front();
}

GPS_POSITION Control_Unit::get_waypoint() {
  return m_waypoint;
}

double Control_Unit::get_distance_threshold() {
  return m_distance_threshold;
}

double Control_Unit::get_waypoint_creation_threshold() {
  return m_waypoint_distance_creation_threshold;
}

void Control_Unit::update_journey() {
  if (m_destination.size() > 0) {
    m_destination.pop();
    m_waypoint_set = false;
    m_waypoint.latitude = 0;
    m_waypoint.longitude = 0;
  } else if (m_destination.size() == 0) {
    std::cout << "JOURNEY COMPLETE!" << std::endl;
    //m_active = false;
  }
}

void Control_Unit::set_waypoint(GPS_POSITION waypoint) {
  m_waypoint.latitude = waypoint.latitude;
  m_waypoint.longitude = waypoint.longitude;
  m_waypoint_set = true;
}

bool Control_Unit::validate_inits(std::vector<bool> statuses) {
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
    std::cout << "[ OK ] : Module Compass" << std::endl;
  } else {
    std::cout << "[ ERROR ] : Module Compass" << std::endl;
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

bool Control_Unit::is_waypoint_set() {
  return m_waypoint_set;
}

void Control_Unit::alternate_angle() {
  if (m_angle_direction == STARBOARD) {
    m_angle_direction = PORT;
  } else {
    m_angle_direction = STARBOARD;
  }
}

ANGLE Control_Unit::get_angle_direction() {
  return m_angle_direction;
}

double Control_Unit::get_distance_factor() {
  return m_distance_factor;
}

bool Control_Unit::time_discrepency_reached(int time_value) {
  if (time_value - m_time_value >= m_time_threshold) {
    std::cout << "TIME LIMIT REACHED" << std::endl;
    return true;
  }
  return false;

}

void Control_Unit::set_time_value(int value) {
  m_time_value = value;
}

void Control_Unit::set_waypoint_status(bool status) {
  m_waypoint_set = status;
}

double Control_Unit::get_calculated_threshold() {
  return m_calculated_threshold;
}
