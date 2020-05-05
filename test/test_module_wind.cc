#include "doctest.h"
#include "../include/module_wind.h"

TEST_CASE("Test ModuleWind") {
  ModuleWind wind;
  wind.Run();
  CHECK(wind.GetReading() != doctest::Approx(-1));
}
