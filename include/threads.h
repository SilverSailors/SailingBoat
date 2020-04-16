#ifndef SAILINGBOAT_INCLUDE_THREADS_H_
#define SAILINGBOAT_INCLUDE_THREADS_H_

class ModuleServo;
class ModuleGPS;
class ModuleCMPS12;
class ModuleWind;
class Logger;

void DriveRudder(ModuleServo &rudder);
void DriveSail(ModuleServo &sail);
void PollGPS(ModuleGPS &gps);
void PollCompass(ModuleCMPS12 &compass);
void PollWind(ModuleWind &wind);
void LogData(Logger &data_logger);

#endif // SAILINGBOAT_INCLUDE_THREADS_H_
