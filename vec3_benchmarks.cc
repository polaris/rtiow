#include <catch2/benchmark/catch_benchmark_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "vec3.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"

TEST_CASE("Vector construction and accessors", "[vec3]") {
  BENCHMARK("Create default vec3") {
    vec3 v;
  };

  BENCHMARK("Create vec3 with specific values") { vec3 v(1.0, 2.0, 3.0); };

  BENCHMARK("Access vec3 elements") {
    vec3 v(1.0, 2.0, 3.0);
    double x = v.x();
    double y = v.y();
    double z = v.z();
  };

  BENCHMARK("Add vec3") {
    vec3 v1(1.0, 2.0, 3.0);
    vec3 v2(4.0, 5.0, 6.0);
    vec3 v = v1 + v2;
  };

  BENCHMARK("Multiply vec3") {
    vec3 v(1.0, 2.0, 3.0);
    double t = 2.0;
    v *= t;
  };

  BENCHMARK("Divide vec3") {
    vec3 v(1.0, 2.0, 3.0);
    double t = 2.0;
    v /= t;
  };

  BENCHMARK("Length of vec3") {
    vec3 v(1.0, 2.0, 3.0);
    double len = v.length();
  };

  BENCHMARK("Squared Length of vec3") {
    vec3 v(1.0, 2.0, 3.0);
    double len_sqr = v.length_squared();
  };

  BENCHMARK("Create random vec3") { vec3 v = vec3::random(); };

  BENCHMARK("Create random vec3 with range") {
    vec3 v = vec3::random(-1.0, 1.0);
  };
}

#pragma GCC diagnostic pop
#pragma clang diagnostic pop
