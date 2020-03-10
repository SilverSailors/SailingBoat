#ifndef __MODULE_SERVO_HPP__
#define __MODULE_SERVO_HPP__
#include "../../Hardware/MAESTRO/MAESTRO.hpp"
class Module_SERVO
{
	private:
		bool 	m_initialized;

		double	m_upper_boundary;
		double	m_lower_boundary;

		int		m_channel;

		double	m_target;

		MAESTRO	m_servo_hardware_connection;

	public:
		Module_SERVO(double lower_limit, double upper_limit, int channel);

		bool init();

		void run();
		void set_target(double limit);
		
};
#endif//__MODULE_SERVO_HPP__
