#include "doctest.h"
#include "../include/utilities.h"

TEST_CASE("Test DegreesToRadians") {
  CHECK(Utilities::DegreesToRadians(100) == doctest::Approx(1.74533));
}