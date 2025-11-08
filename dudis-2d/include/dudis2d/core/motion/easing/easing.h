#pragma once

//  constexpr float PI = 3.14159265359f;
// #include <cmath>

namespace dudis {
#define DDPI 3.14159265359f
} // namespace dudis

#pragma once
// #include <cmath>

namespace dudis {
class Easing {
public:
  static float easeIn(float t);
  static float easeOut(float t);
  static float easeInOut(float t);
  static float easeElastic(float t);
  static float easeBounce(float t);
};
} // namespace dudis