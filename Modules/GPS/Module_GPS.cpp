#include "Module_GPS.hpp"
#include <iostream>
Module_GPS::Module_GPS()
{
	std::cout << "Constructing [Module] GPS Module" << std::endl;
	m_initialized = false;
    m_new_data_available = false;
}

bool Module_GPS::init()
{
	bool result = m_gps_hardware_connection.init();
	m_initialized = result;
	return result;
}

void Module_GPS::run()
{
	if(m_initialized)
	{
		GPS_DATA reading = m_gps_hardware_connection.read();
		if(reading.get_valid())
		{
			m_data_reading = reading;
			m_new_data_available = true;
		}
		else
		{
			std::cout << "GPS: DATA READING NOT VALID" << std::endl;
		}
	}
}

GPS_DATA Module_GPS::get_reading()
{
	return m_data_reading;
}

void Module_GPS::report()
{
	if(m_new_data_available)
	{
			std::cout << "- - GPS SENSOR - -" << std::endl;
			std::cout << "GPS LAT : " << m_data_reading.get_latitude() << std::endl;
			std::cout << "GPS LON : " << m_data_reading.get_longitude() << std::endl;
			std::cout << "GPS TIME: " << m_data_reading.get_time() << std::endl;
			std::cout << "GPS TIME: " << m_data_reading.get_time_value() << std::endl;
			std::cout << "------------------" << std::endl;
			m_new_data_available = false;
	}
}

bool Module_GPS::is_new_data_avilable()
{
    return m_new_data_available;
}
