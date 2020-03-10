#include "GPS_data.hpp"
#include <string>
GPS_DATA::GPS_DATA()
{
	m_valid = false;
	m_latitude	= 0;
	m_longitude = 0;
	m_speed 		= 0;
	m_time = "";
	m_time_value = 0;
}

void GPS_DATA::set_latitude(double latitude)
{
	m_latitude = latitude;
}

void GPS_DATA::set_longitude(double longitude)
{
	m_longitude = longitude;
}

void GPS_DATA::set_timestamp(std::string timestamp)
{
	m_time = timestamp;
}

void GPS_DATA::set_valid(bool valid)
{
	m_valid = valid;
}

bool GPS_DATA::get_valid()
{
	return m_valid;
}

double GPS_DATA::get_latitude()
{
	return m_latitude;
}

double GPS_DATA::get_longitude()
{
	return m_longitude;
}

std::string GPS_DATA::get_time()
{
	return m_time;
}

double GPS_DATA::get_speed()
{
	return m_speed;
}

void GPS_DATA::set_speed(double speed)
{
	m_speed = speed;
}

void GPS_DATA::set_time_value(double value)
{
    m_time_value = value;
}

double GPS_DATA::get_time_value()
{
    return m_time_value;
}
