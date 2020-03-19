#include "../include/utilities.h"
#include "doctest.h"

TEST_CASE("test degrees to radians STAND ALONE") {
  CHECK(Utilities::DegreesToRadians(100) == doctest::Approx(1.74533));
}
