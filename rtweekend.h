#ifndef RTWEEKEND_H
#define RTWEEKEND_H

// #include <chrono>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
// #include <random>

// Usings

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double clamp(double x, double min, double max) {
  if (x < min)
    return min;
  if (x > max)
    return max;
  return x;
}

inline double random_double() {
  // Returns a random real in [0,1).
  return rand() / (RAND_MAX + 1.0);
}

// inline double random_double() {
//   // Use a static generator and distribution to avoid reinitialization.
//   static std::mt19937 generator(static_cast<unsigned int>(
//       std::chrono::system_clock::now().time_since_epoch().count()));
//   static std::uniform_real_distribution<double> distribution(0.0, 1.0);

//   // Generate a random double using the distribution and return it.
//   return distribution(generator);
// }

inline double random_double(double min, double max) {
  // Returns a random real in [min,max).
  return min + (max - min) * random_double();
}

inline int random_int(int min, int max) {
  // Returns a random integer in [min,max].
  return static_cast<int>(random_double(min, max + 1));
}

#endif
