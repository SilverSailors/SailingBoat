#include "../include/module_wind.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../include/json.hpp"

ModuleWind::ModuleWind() {
  std::cout << "Constructing [Module] Wind" << std::endl;
  initialized_ = false;
  new_data_available_ = false;
}

bool ModuleWind::Init() {
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

void ModuleWind::Run() {
  if (initialized_) {
    std::string data;
    curl_easy_setopt(curl_, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=Mariehamn,ax&appid=e9877347da3a765b545040c9d6aa0e74");
    curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &data);
    curl_easy_perform(curl_);
    curl_easy_cleanup(curl_);
    nlohmann::json json_obj;
    std::stringstream(data) >> json_obj;
    wind_speed_reading_ = json_obj["wind"]["speed"];
    wind_deg_reading_ = json_obj["wind"]["deg"];
    new_data_available_ = true;
  }
}

bool ModuleWind::IsNewDataAvailable() {
  return new_data_available_;
}

double ModuleWind::GetWindSpeedReading() {
  return wind_speed_reading_;
}

int ModuleWind::GetWindDegReading() {
  return wind_deg_reading_;
}

void ModuleWind::Report() {
  if (new_data_available_) {
    std::cout << "- - WIND - -" << std::endl;
    std::cout << "Wind Speed: " << wind_speed_reading_ << std::endl;
    std::cout << "Wind Bearing: " << wind_deg_reading_ << std::endl;
    std::cout << "-------------------" << std::endl;
    new_data_available_ = false;
  }
}
