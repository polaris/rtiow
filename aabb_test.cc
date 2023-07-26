#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include "aabb.h"

TEST_CASE("AABB construction and accessors", "[aabb]") {
  point3 min(0, 0, 0);
  point3 max(1, 1, 1);
  aabb box(min, max);

  REQUIRE(box.min() == min);
  REQUIRE(box.max() == max);
}

TEST_CASE("Testing aabb class and its methods", "[aabb]") {
  point3 p1(0, 0, 0);
  point3 p2(5, 5, 6);
  aabb box1(p1, p2);

  SECTION("Testing min/max methods") {
    REQUIRE(box1.min().x() == 0);
    REQUIRE(box1.min().y() == 0);
    REQUIRE(box1.min().z() == 0);
    REQUIRE(box1.max().x() == 5);
    REQUIRE(box1.max().y() == 5);
    REQUIRE(box1.max().z() == 6);
  }

  SECTION("Testing area method") {
    REQUIRE(box1.area() == Catch::Approx(170.0));
  }

  SECTION("Testing longest_axis method") { REQUIRE(box1.longest_axis() == 2); }

  SECTION("Ray originates inside the box") {
    ray r(point3(3, 3, 3), point3(1, 1, 1));
    REQUIRE(box1.hit(r, 0, 10) == true);
  }

  SECTION("Ray originates outside the box and goes towards it") {
    ray r(point3(-1, -1, -1), point3(1, 1, 1));
    REQUIRE(box1.hit(r, 0, 10) == true);
  }

  SECTION("Ray originates outside the box and goes away from it") {
    ray r(point3(-1, -1, -1), point3(-1, -1, -1));
    REQUIRE(box1.hit(r, 0, 10) == false);
  }

  SECTION("Ray is parallel to the box") {
    ray r(point3(6, 0, 0), point3(0, 1, 0));
    REQUIRE(box1.hit(r, 0, 10) == false);
  }

  SECTION("Ray intersects the box edge") {
    ray r(point3(0, 0, -1), point3(0, 0, 1));
    REQUIRE(box1.hit(r, 0, 10) == false);
  }

  SECTION("Ray just misses the box") {
    ray r(point3(0, 0, 7), point3(0, 0, -1));
    REQUIRE(box1.hit(r, 0, 10) == false);
  }

  SECTION("Ray intersects the box but t_max is too small") {
    ray r(point3(-1, -1, -1), point3(1, 1, 1));
    REQUIRE(box1.hit(r, 0, 0.1) == false);
  }

  SECTION("Ray intersects the box but t_min is too large") {
    ray r(point3(-1, -1, -1), point3(1, 1, 1));
    REQUIRE(box1.hit(r, 10, 20) == false);
  }

  SECTION("Testing surrounding_box function") {
    point3 p3(4, 4, 4);
    point3 p4(6, 6, 7);
    aabb box2(p3, p4);

    aabb surrounding = surrounding_box(box1, box2);
    REQUIRE(surrounding.min().x() == 0);
    REQUIRE(surrounding.min().y() == 0);
    REQUIRE(surrounding.min().z() == 0);
    REQUIRE(surrounding.max().x() == 6);
    REQUIRE(surrounding.max().y() == 6);
    REQUIRE(surrounding.max().z() == 7);
  }
}
