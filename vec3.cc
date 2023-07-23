#include "vec3.h"

bool operator==(const vec3 &u, const vec3 &v) {
  return (u.e[0] == v.e[0]) && (u.e[1] == v.e[1]) && (u.e[2] == v.e[2]);
}

bool operator!=(const vec3 &u, const vec3 &v) { return !(u == v); }
