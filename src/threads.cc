#include "../include/module_servo.h"
#include "../include/module_gps.h"
#include "../include/module_cmps12.h"
#include "../include/module_wind.h"
#include "../include/logger.h"
#include <thread>
#include <chrono>

void DriveRudder(ModuleServo &rudder) {
  while (true) {
    rudder.Run();
  }
}

void DriveSail(ModuleServo &sail) {
  while (true) {
    sail.Run();
  }
}

void PollGPS(ModuleGPS &gps) {
  while (true) {
    gps.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void PollCompass(ModuleCMPS12 &compass) {
  while (true) {
    compass.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

void PollWind(ModuleWind &wind) {
  while (true) {
    wind.Run();
    std::this_thread::sleep_for(std::chrono::milliseconds(5*60000));
  }
}

void LogData(Logger &data_logger) {
  std::this_thread::sleep_for(std::chrono::milliseconds(6000));
  while (true) {
    data_logger.Publish();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
  }
}

