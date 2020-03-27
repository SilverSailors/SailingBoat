#include "doctest.h"
#include "../include/module_wind.h"

TEST_CASE("Test ModuleWind") {
  ModuleWind wind;
  wind.Init();
  wind.Run();
  CHECK(wind.GetWindSpeedReading() >= 0);
  CHECK(wind.GetWindDegReading() >= 0);
}
