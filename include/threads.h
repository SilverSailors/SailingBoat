#ifndef SAILINGBOAT_INCLUDE_THREADS_H_
#define SAILINGBOAT_INCLUDE_THREADS_H_

class ModuleServo;
class ModuleGPS;
class ModuleCMPS12;
class ModuleWind;
class Logger;

/**
 * Thread for updating a servo module
 * @param rudder ModuleServo object
 */
void DriveRudder(ModuleServo &rudder);
/**
 * Thread for updating a servo module
 * @param sail ModuleServo object
 */
void DriveSail(ModuleServo &sail);
/**
 * Thread for updating the GPS module
 * @param gps ModuleGPS object
 */
void PollGPS(ModuleGPS &gps);
/**
 * Thread for updating the CMPS12 module
 * @param compass ModuleCMPS12 object
 */
void PollCompass(ModuleCMPS12 &compass);
/**
 * Thread for updating the wind module
 * @param wind
 */
void PollWind(ModuleWind &wind);
/**
 * Thread for logging journey
 * @param data_logger
 */
void LogData(Logger &data_logger);

#endif // SAILINGBOAT_INCLUDE_THREADS_H_
