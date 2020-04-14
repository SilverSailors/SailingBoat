#include "../include/module_wind.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../include/json.hpp"

ModuleWind::ModuleWind() {
  /* Get a curl handle */
  curl_ = curl_easy_init();
  initialized_ = curl_ != nullptr;
  data_reading_ = -1;
  new_data_available_ = false;
}

ModuleWind::ModuleWind(int wind_deg) {
  curl_ = nullptr;
  initialized_ = true;
  data_reading_ = wind_deg;
  new_data_available_ = true;
}

ModuleWind::~ModuleWind() {
  /* Always cleanup */
  if (curl_) curl_easy_cleanup(curl_);
}

bool ModuleWind::GetInitialized() {
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
    /* Perform the request */
    curl_easy_perform(curl_);

    nlohmann::json json_obj;
    std::stringstream(data) >> json_obj;
    data_reading_ = json_obj["wind"]["deg"];
    new_data_available_ = true;
  }
}

int ModuleWind::GetReading() {
  return data_reading_;
}

void ModuleWind::Report() {
  if (new_data_available_) {
    std::cout << "Wind angle              : " << data_reading_ << std::endl;
    new_data_available_ = false;
  }
}
