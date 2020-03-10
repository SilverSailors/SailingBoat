#ifndef __MODULE_WIND_SENSOR_HPP__
#define __MODULE_WIND_SENSOR_HPP__
#include "../../Hardware/MA3/MA3.hpp"
class Module_Wind_Sensor
{
	private:
		bool m_initialized;

		MA3 m_hardware_connection_MA3;

		int m_spi_channel;

		int m_reading;

		double m_internal_offset;

		//Have we read the latest reading already?
		bool m_new_data_available;

	public:
		Module_Wind_Sensor(int spi_channel);
		bool	init();
		void 	run();
		int 	get_reading();
		void 	report();
    bool  is_new_data_avilable();
};
#endif//__MODULE_WIND_SENSOR_HPP__
