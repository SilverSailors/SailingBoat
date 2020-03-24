#include "doctest.h"
#include "../include/module_wind.h"

TEST_CASE("Test ModuleWind") {
  ModuleWind wind;
  wind.Init();
  wind.Run();
  CHECK(wind.GetWindSpeedReading() != doctest::Approx(-1.0));
  CHECK(wind.GetWindDegReading() != doctest::Approx(-1));
}
