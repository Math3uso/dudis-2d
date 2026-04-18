#pragma once

// temp

// inline float lerp(float a, float b, float t)
// {
//   return a + (b - a) * t;
// }

// temp

namespace dudis
{
#define DDPI 3.14159265359f
} // namespace dudis

namespace dudis
{
  class Easing
  {
  public:
    static float EaseIn(float t);
    static float EaseOut(float t);
    static float EaseInOut(float t);
    static float EaseElastic(float t);
    static float EaseBounce(float t);
  };
} // namespace dudis