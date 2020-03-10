#include "CMPS12.hpp"
#include <iostream>
#include <vector>
#include "CMPS12_I2C_registry.hpp"
#include <wiringPi.h>
#include <wiringPiI2C.h>
CMPS12::CMPS12()
{
    m_file_descriptor = 0;
    m_initialized   = false;
}

int CMPS12::bitshift(int high, int low)
{
    int result = (high << 8 | low);
    return result;
}

bool CMPS12::init()
{
    std::cout << "CMPS Hardware Initializing" << std::endl;
    wiringPiSetup();
    m_file_descriptor = wiringPiI2CSetup(I2C_DEVICE_ADDRESS);
    if(m_file_descriptor == -1)
    {
        std::cout << "CMPS Hardware Failed to Initialize" << std::endl;
        m_initialized = false;
    }
    m_initialized = true;
    return m_initialized;
}

CMPS12_DATA CMPS12::read()
{
    CMPS12_DATA compass_data;

    //Read data if we are initialized
    if(m_initialized)
    {
        std::vector<int> raw_data;
        //Reserve 31 Slots for our raw data
        raw_data.reserve(31);

        for(int i = 0; i < TOTAL_REGISTRY_ENTRIES; i++)
        {
            raw_data[i] = wiringPiI2CReadReg8(m_file_descriptor,i);
        }

        //Check if calibration was valid (If yes then usually the data was OK read)
        if(raw_data[CALIBRATION_STATE_8] == -1)
        {
            compass_data.set_valid(false);
            return compass_data;
        }

        //Data set is valid
        compass_data.set_valid(true);



        //Bitshift relevant required data
        int bearing_16 = bitshift(
        raw_data[COMPASS_BEARING_16_HIGH_BYTE_DEGREES],raw_data[COMPASS_BEARING_16_LOW_BYTE_DEGREES]) / 16;

        //data_set.set_entry()
        compass_data.set_entry(DATA_SET_CALIBRATION_STATE_8, raw_data[CALIBRATION_STATE_8]);
        compass_data.set_entry(DATA_SET_ROLL_ANGLE_8, raw_data[ROLL_ANGLE_8]);
        compass_data.set_entry(DATA_SET_PITCH_ANGLE_8, raw_data[PITCH_ANGLE_8]);
        compass_data.set_entry(DATA_SET_COMPASS_BEARING_DEGREES_16, bearing_16);

        return compass_data;
    }
    else
    {
        std::cout << "CMPS Hardware Not Initialized" << std::endl;
        return compass_data;
    }

}
