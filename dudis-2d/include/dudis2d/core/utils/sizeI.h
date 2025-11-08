#pragma once

namespace dudis {
class SizeI {
public:
  int w;
  int h;

  SizeI(int w, int h) : w(w), h(h) {}
  SizeI() : w(0), h(0) {}

  bool operator==(const SizeI &other) const {
    return w == other.w && h == other.h;
  }

  SizeI operator+(const SizeI &other) const {
    return SizeI(w + other.w, h + other.h);
  }
};
} // namespace dudis