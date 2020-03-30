#ifndef SAILINGBOAT_INCLUDE_MODULE_WIND_H_
#define SAILINGBOAT_INCLUDE_MODULE_WIND_H_
#include <curl/curl.h>

class ModuleWind {
 public:
  /**
   * The constructor, initializes member fields
   */
  ModuleWind();
  /**
   * The destructor, cleans up
   */
  ~ModuleWind();
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
   * Returns "wind_speed_reading_" member field
   * @return "wind_speed_reading_" value
   */
   double GetWindSpeedReading();
  /**
   * Returns "wind_deg_reading_" member field
   * @return "wind_deg_reading_" value
   */
  int GetWindDegReading();
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
  double wind_speed_reading_;
  /**
  * The latest wind deg reading
  */
  int wind_deg_reading_;
};

#endif //SAILINGBOAT_INCLUDE_MODULE_WIND_H_
