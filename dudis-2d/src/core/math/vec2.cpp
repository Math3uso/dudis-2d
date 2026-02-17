#include "dudis2d/core/math/vec2.h"

#include <cmath>

using namespace dudis;

bool Vec2::operator==(const Vec2 &other) const { return x == other.x && y == other.y; }

bool Vec2::operator!=(const Vec2 &other) const { return !(*this == other); }

Vec2 Vec2::operator+(const Vec2 &other) const { return Vec2{x + other.x, y + other.y}; }

Vec2 Vec2::operator-(const Vec2 &other) const { return Vec2{x - other.x, y - other.y}; }

Vec2 &Vec2::operator+=(const Vec2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vec2 &Vec2::operator-=(const Vec2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vec2 &Vec2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vec2 &Vec2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vec2 Vec2::operator-() const { return Vec2{-x, -y}; }

float Vec2::length() const { return std::sqrt(lengthSquared()); }

float Vec2::lengthSquared() const { return x * x + y * y; }

Vec2 Vec2::normalized() const {
    const float len = length();
    return (len > 0.f) ? Vec2{x / len, y / len} : Vec2{0.f, 0.f};
}

float Vec2::dot(const Vec2 &a, const Vec2 &b) { return a.x * b.x + a.y * b.y; }

Vec2 dudis::operator*(Vec2 vec, float scalar) {
    vec *= scalar;
    return vec;
}

Vec2 dudis::operator*(float scalar, Vec2 vec) {
    vec *= scalar;
    return vec;
}

Vec2 dudis::operator/(Vec2 vec, float scalar) {
    vec /= scalar;
    return vec;
}
