#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/globals/app.h"
#include "raylib.h"
#include <box2d/box2d.h>
#include <iostream>
#include <memory>

namespace dudis {
using Vec2 = Vector2;
using Vec3 = Vector3;
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