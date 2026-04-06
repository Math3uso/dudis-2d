#pragma once

#include <memory>

namespace dudis
{

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
}