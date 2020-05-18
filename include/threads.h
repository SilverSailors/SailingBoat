#ifndef SAILINGBOAT_INCLUDE_THREADS_H_
#define SAILINGBOAT_INCLUDE_THREADS_H_

class ModuleServo;
class ModuleGPS;
class ModuleCompass;
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
 * Thread for updating the Compass module
 * @param compass ModuleCompass object
 */
void PollCompass(ModuleCompass &compass);
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
