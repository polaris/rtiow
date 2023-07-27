#include <catch2/catch_test_macros.hpp>

#include "vec3.h"

TEST_CASE("Vector construction and accessors", "[vec3]") {
  vec3 v(1, 2, 3);

  REQUIRE(v.x() == 1);
  REQUIRE(v.y() == 2);
  REQUIRE(v.z() == 3);
}