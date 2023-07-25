#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
  constexpr ray() : orig_(), dir_(), tm_(0.0) {}
  constexpr ray(const point3 &origin, const vec3 &direction, double time = 0.0)
      : orig_(origin), dir_(direction), tm_(time) {}

  constexpr point3 origin() const { return orig_; }
  constexpr vec3 direction() const { return dir_; }
  constexpr double time() const { return tm_; }

  constexpr point3 at(double t) const { return orig_ + t * dir_; }

private:
  point3 orig_;
  vec3 dir_;
  double tm_;
};

#endif
