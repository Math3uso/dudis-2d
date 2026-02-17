#include "dudis2d/core/math/vec4.h"

#include <cmath>

using namespace dudis;

bool Vec4::operator==(const Vec4 &other) const {
    return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Vec4::operator!=(const Vec4 &other) const { return !(*this == other); }

Vec4 Vec4::operator+(const Vec4 &other) const {
    return Vec4{x + other.x, y + other.y, z + other.z, w + other.w};
}

Vec4 Vec4::operator-(const Vec4 &other) const {
    return Vec4{x - other.x, y - other.y, z - other.z, w - other.w};
}

Vec4 &Vec4::operator+=(const Vec4 &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;
    return *this;
}

Vec4 &Vec4::operator-=(const Vec4 &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;
    return *this;
}

Vec4 &Vec4::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

Vec4 &Vec4::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

Vec4 Vec4::operator-() const { return Vec4{-x, -y, -z, -w}; }

float Vec4::length() const { return std::sqrt(lengthSquared()); }

float Vec4::lengthSquared() const { return x * x + y * y + z * z + w * w; }

Vec4 Vec4::normalized() const {
    const float len = length();
    return (len > 0.f) ? Vec4{x / len, y / len, z / len, w / len}
                       : Vec4{0.f, 0.f, 0.f, 0.f};
}

float Vec4::dot(const Vec4 &a, const Vec4 &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vec4 dudis::operator*(Vec4 vec, float scalar) {
    vec *= scalar;
    return vec;
}

Vec4 dudis::operator*(float scalar, Vec4 vec) {
    vec *= scalar;
    return vec;
}

Vec4 dudis::operator/(Vec4 vec, float scalar) {
    vec /= scalar;
    return vec;
}
