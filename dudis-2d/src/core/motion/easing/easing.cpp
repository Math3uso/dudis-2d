#include "dudis2d/core/motion/easing/easing.h"
#include <cmath>

namespace dudis {

float Easing::easeIn(float t) { return t * t; }

float Easing::easeOut(float t) { return t * (2 - t); }

float Easing::easeInOut(float t) {
  return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

float Easing::easeElastic(float t) {
  return std::sin(t * DDPI * 4) * std::pow(2, -10 * t) + 1;
}

float Easing::easeBounce(float t) {
  if (t < 0.3636f)
    return 7.5625f * t * t;
  else if (t < 0.7272f) {
    t -= 0.5454f;
    return 7.5625f * t * t + 0.75f;
  } else if (t < 0.9090f) {
    t -= 0.8181f;
    return 7.5625f * t * t + 0.9375f;
  } else {
    t -= 0.9545f;
    return 7.5625f * t * t + 0.984375f;
  }
}

} // namespace dudis
