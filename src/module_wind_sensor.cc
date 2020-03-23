#include "../include/module_wind_sensor.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../include/json.hpp"
#include "../test/doctest.h"

ModuleWindSensor::ModuleWindSensor() {
  std::cout << "Constructing [Module] Wind Sensor" << std::endl;
  initialized_ = false;
  new_data_available_ = false;
  wind_speed_ = -1.0;
  reading_ = -1;
}

bool ModuleWindSensor::Init() {
  curl_ = curl_easy_init();
  if(curl_) {
    initialized_ = true;
  }
  return initialized_;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

void ModuleWindSensor::Run() {
  if (initialized_) {
    std::string data;
    curl_easy_setopt(curl_, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=Mariehamn,ax&appid=e9877347da3a765b545040c9d6aa0e74");
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(curl_);
    nlohmann::json json_obj;
    std::stringstream(data) >> json_obj;
    reading_ = json_obj["wind"]["deg"];
    wind_speed_ = json_obj["wind"]["speed"];
    new_data_available_ = true;
  }
}

TEST_CASE("testing module wind sensor") {
  ModuleWindSensor sensor;
  sensor.Init();
  sensor.Run();
  sensor.Report();
  CHECK(sensor.GetReading() != -1);
  CHECK(sensor.GetWindSpeed() != doctest::Approx(-1.0));
}

bool ModuleWindSensor::IsNewDataAvailable() {
  return new_data_available_;
}

int ModuleWindSensor::GetReading() {
  return reading_;
}

double ModuleWindSensor::GetWindSpeed() {
  return wind_speed_;
}

void ModuleWindSensor::Report() {
  if (new_data_available_) {
    std::cout << "- - WIND SENSOR - -" << std::endl;
    std::cout << "Wind Bearing: " << reading_ << std::endl;
    std::cout << "Wind Speed: " << wind_speed_ << std::endl;
    std::cout << "-------------------" << std::endl;
    new_data_available_ = false;
  }
}
