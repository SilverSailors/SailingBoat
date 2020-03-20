#ifndef SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
#define SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
#include <curl/curl.h>

class ModuleWindSensor {
 public:
  /**
   * The constructor, initializes member fields
   */
  ModuleWindSensor();
  /**
   * Initializes "curl_"
   * @return boolean on successful initialization
   */
  bool Init();
  /**
   * Runs module, reads data from api and saves it
   */
  void Run();
  /**
   * Returns "new_data_available_" member field
   * @return "new_data_available_" boolean value
   */
  bool IsNewDataAvailable();
  /**
   * Returns "reading_" member field
   * @return "reading_" value
   */
  int GetReading();
  /**
   * Reports the latest reading
   */
  void Report();
 private:
  /**
   * CURL library for api fetching
   */
  CURL *curl_;
  /**
   * If ModuleWindSensor is initialized
   */
  bool initialized_;
  /**
   * Is new data available for reading
   */
  bool new_data_available_;
  /**
   * The latest reading
   */
  int reading_;
};

#endif // SAILINGBOAT_INCLUDE_MODULE_WIND_SENSOR_H_
