#ifndef SAILINGBOAT_INCLUDE_MODULE_WIND_H_
#define SAILINGBOAT_INCLUDE_MODULE_WIND_H_
#include <curl/curl.h>

class ModuleWind {
 public:
  /**
   * A constructor, initializes member fields
   */
  ModuleWind();
  /**
   * A constructor, uses hardcoded value for wind
   * @param wind_deg Wind direction value
   */
  ModuleWind(int wind_deg);
  /**
   * The destructor, closes api
   */
  ~ModuleWind();
  /**
   * Returns "initialized_" member field value
   * @return "initialized_" object
   */
  bool GetInitialized();
  /**
   * Runs module, reads data from api and saves it
   */
  void Run();
  /**
   * Returns "data_reading_" member field
   * @return "data_reading_" value
   */
   int GetReading();
  /**
   * Reports the latest reading
   */
  void Report();
 private:
  /**
   * CURL library
   */
  CURL *curl_;
  /**
   * If ModuleWind is initialized
   */
  bool initialized_;
  /**
   * Is new data available for reading
   */
  bool new_data_available_;
  /**
   * The latest wind speed reading
   */
  int data_reading_;
};

#endif //SAILINGBOAT_INCLUDE_MODULE_WIND_H_
