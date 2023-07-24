#include <catch2/catch_test_macros.hpp>

#include "aabb.h"

TEST_CASE("AABB construction and accessors", "[aabb]") {
  point3 min(0, 0, 0);
  point3 max(1, 1, 1);
  aabb box(min, max);

  REQUIRE(box.min() == min);
  REQUIRE(box.max() == max);
}
