#pragma once

#include "dudis2d/core/utils/sizeI.h"
#include "dudis2d/globals/app.h"
#include "raylib.h"

#include "dudis2d/core/math/vec2.h"

#include <iostream>
#include <memory>
#include "dudis2d/core/math/rect.h"

#include "dudis2d/core/utils/sizeF.h"

namespace rl
{
  using RlTexture = Texture2D;
  using rlFont = Font;

} // namespace rl

namespace dudis
{

  using Size = SizeF;

  template <typename T>
  using Scope = std::unique_ptr<T>;
  template <typename T>
  constexpr auto SetScope = [](auto &&arg) -> decltype(auto)
  {
    return std::move(std::forward<decltype(arg)>(arg));
  };

  template <typename T, typename... Args>
  dudis::Scope<T> CreateScope(Args &&...args)
  {
    auto scope = std::make_unique<T>(std::forward<Args>(args)...);
    return scope;
  }

} // namespace dudis

enum class DDPrimitiveType
{
  Fill,
  Lines,
  Points,
};

enum class DDBatchType
{
  Shapes,
  Textures,
};