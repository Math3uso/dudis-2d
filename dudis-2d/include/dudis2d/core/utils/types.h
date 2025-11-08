#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/globals/app.h"
#include "raylib.h"
#include <box2d/box2d.h>
#include <iostream>
#include <memory>

extern int drawCallCounter; // variável interna do rlgl.c

namespace dudis {

// int GetDrawCalls(void) { return drawCallCounter; }

using Vec2 = Vector2;
using Vec3 = Vector3;

// class Vec2 {
// public:
//   float x;
//   float y;

//   Vec2(float x, float y) : x(x), y(y) {}
//   Vec2() : x(0), y(0) {}

//   bool operator==(const Vec2 &other) const {
//     return x == other.x && y == other.y;
//   }

//   Vec2 operator+(const Vec2 &other) const {
//     return Vec2(x + other.x, y + other.y);
//   }

//   Vec2 operator-(const Vec2 &other) const {
//     return Vec2(x - other.x, y - other.y);
//   }

//   Vec2 operator+=(const Vec2 &other) {
//     x += other.x;
//     y += other.y;
//     return *this;
//   }

//   Vec2 operator-=(const Vec2 &other) {
//     x -= other.x;
//     y -= other.y;
//     return *this;
//   }

//   Vec2 operator=(const b2Vec2 &other) {
//     x = other.x;
//     y = other.y;
//     return *this;
//   }

//   Vector2 toRaylibVec2() const { return Vector2{x, y}; }
// };

using Size = SizeI;

template <typename T> using Scope = std::unique_ptr<T>;
template <typename T>
constexpr auto SetScope = [](auto &&arg) -> decltype(auto) {
  return std::move(std::forward<decltype(arg)>(arg));
};

template <typename T, typename... Args>
dudis::Scope<T> CreateScope(Args &&...args) {
  auto scope = std::make_unique<T>(std::forward<Args>(args)...);
  return scope;
}

} // namespace dudis