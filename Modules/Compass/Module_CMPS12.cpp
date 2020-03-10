#include <iostream>
#include "Module_CMPS12.hpp"
#include "../../Core/IO/IO.hpp"
#include "../../Core/Parser/Parser.hpp"
#include "../../Utilities/utilities.hpp"

Module_CMPS12::Module_CMPS12() {
  std::cout << "Constructing [Module] : CMPS12" << std::endl;
  m_initialized = false;
  m_new_data_available = false;
}

Module_CMPS12::~Module_CMPS12() {

}

bool Module_CMPS12::init() {
  std::cout << "Module Initializing" << std::endl;

  bool state = m_CMPS12_hardware_connection.init();
  m_initialized = state;

  IO io;
  Parser parser;
  std::vector<std::string> data_raw = io.read_file("Settings/sensor_config.txt");
  std::vector<std::string> data_clean = parser.remove_comments(data_raw);
  m_internal_offset = std::atof(data_clean[0].c_str());
  std::cout << "Internal Offset (COMPASS): " << m_internal_offset << std::endl;
  return state;
}

void Module_CMPS12::run() {
  if (m_initialized) {
    CMPS12_DATA data;
    data = m_CMPS12_hardware_connection.read();
    if (data.get_valid()) {
      m_CMPS12_data_reading = data;
      m_new_data_available = true;
      int bearing = m_CMPS12_data_reading.get_entry(DATA_SET_COMPASS_BEARING_DEGREES_16);
      int calibrated = Utilities::normalize(bearing + m_internal_offset);
      m_CMPS12_data_reading.set_entry(DATA_SET_COMPASS_BEARING_DEGREES_16, calibrated);

    } else {
      std::cout << "CONNECTION ERROR: CHECK CABLING" << std::endl;
    }
  }
}

bool Module_CMPS12::getInitialized() {
  return m_initialized;
}

CMPS12_DATA Module_CMPS12::get_reading() {
  return m_CMPS12_data_reading;
}

void Module_CMPS12::report() {
  if (m_new_data_available) {
    std::cout << "- - COMPASS SENSOR - -" << std::endl;
    std::cout << "Bearing: " << m_CMPS12_data_reading.get_entry(DATA_SET_COMPASS_BEARING_DEGREES_16) << std::endl;
    std::cout << "Pitch  : " << m_CMPS12_data_reading.get_entry(DATA_SET_PITCH_ANGLE_8) << std::endl;
    std::cout << "Roll   : " << m_CMPS12_data_reading.get_entry(DATA_SET_ROLL_ANGLE_8) << std::endl;
    std::cout << "----------------------" << std::endl;
    m_new_data_available = false;
  }

}

bool Module_CMPS12::is_new_data_avilable() {
  return m_new_data_available;
}
