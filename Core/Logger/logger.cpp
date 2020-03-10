#include "logger.hpp"
#include <string>
#include "../IO/IO.hpp"
#include "../../Hardware/GPS/GPS_data.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

Logger::Logger(std::string path) {
  m_entries = 0;
  m_file_path = path;

}

void Logger::log_data(LOG packet) {
  m_log.m_latitude = packet.m_latitude;
  m_log.m_longitude = packet.m_longitude;
  m_log.m_timestamp = packet.m_timestamp;

  m_available = true;
}

void Logger::publish() {
  if (m_available) {
    //int bearing             = m_log.m_bearing;
    double latitude = m_log.m_latitude;
    double longitude = m_log.m_longitude;
    //double speed            = m_log.m_speed;
    std::string timestamp = m_log.m_timestamp;
    //double waypoint         = m_log.m_distance_from_waypoint;
    //double checkpoint       = m_log.m_distance_from_destination;

    std::stringstream stream;
    stream << timestamp << " " << std::setprecision(15) << latitude << " " << std::setprecision(15) << longitude;

    std::string output = stream.str();

    IO io;
    io.write_file(output, m_file_path);
    m_entries++;
    m_available = false;
  } else {
    std::cout << "NO NEW LOG AVAILABLE" << std::endl;
  }
}

void Logger::publish_waypoint(GPS_DATA from, GPS_POSITION to, std::string message) {
  std::string timestamp = from.get_time();
  double at_lat = from.get_latitude();
  double at_lon = from.get_longitude();

  double dest_lat = to.latitude;
  double dest_lon = to.longitude;

  std::stringstream stream;
  stream << timestamp
         << " : "
         << std::setprecision(10) << at_lat
         << " "
         << std::setprecision(10) << at_lon
         << " (->) "
         << std::setprecision(10) << dest_lat
         << " "
         << std::setprecision(10) << dest_lon;
  std::string output = stream.str();

  IO io;
  io.write_file(output + " : " + message, m_file_path);
  m_entries++;
  m_available = false;

}

void Logger::write(std::string message) {
  std::stringstream stream;
  stream << message;

  IO io;
  io.write_file(message, m_file_path);
}
