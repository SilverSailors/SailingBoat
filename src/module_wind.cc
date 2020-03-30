#include "../include/module_wind.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../include/json.hpp"

ModuleWind::ModuleWind() {
  std::cout << "Constructing [Module] Wind" << std::endl;
  /* Get a curl handle */
  curl_ = curl_easy_init();
  initialized_ = curl_ != nullptr || false;
  new_data_available_ = false;
  wind_speed_reading_ = -1.0;
  wind_deg_reading_ = -1;
}

ModuleWind::~ModuleWind() {
  /* Always cleanup */
  curl_easy_cleanup(curl_);
}

bool ModuleWind::Init() {
  /* No need for initialization here */
  return initialized_;
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}

void ModuleWind::Run() {
  if (curl_) {
    std::string data;
    /* First set the URL that is about to fetched from */
    curl_easy_setopt(curl_, CURLOPT_URL, "http://api.openweathermap.org/data/2.5/weather?q=Mariehamn,ax&appid=e9877347da3a765b545040c9d6aa0e74");
    /* We want to use our own write function */
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    /* Pointer to pass to our write function */
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &data);
    /* Perform the request, res will get the return code */
    CURLcode res = curl_easy_perform(curl_);
    /* Check for errors */
    if (res != CURLE_OK) std::cout << curl_easy_strerror(res) << std::endl;
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
