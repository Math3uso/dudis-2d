#include "dudis2d/core/math/vec3.h"

#include <cmath>

using namespace dudis;

bool Vec3::operator==(const Vec3 &other) const
{
    return x == other.x && y == other.y && z == other.z;
}

bool Vec3::operator!=(const Vec3 &other) const { return !(*this == other); }

Vec3 Vec3::operator+(const Vec3 &other) const
{
    return Vec3{x + other.x, y + other.y, z + other.z};
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3{x - other.x, y - other.y, z - other.z};
}

Vec3 &Vec3::operator+=(const Vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 &Vec3::operator-=(const Vec3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vec3 &Vec3::operator*=(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

Vec3 &Vec3::operator/=(float scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

Vec3 Vec3::operator-() const { return Vec3{-x, -y, -z}; }

float Vec3::length() const { return std::sqrt(lengthSquared()); }

float Vec3::lengthSquared() const { return x * x + y * y + z * z; }

Vec3 Vec3::normalized() const
{
    const float len = length();
    return (len > 0.f) ? Vec3{x / len, y / len, z / len} : Vec3{0.f, 0.f, 0.f};
}

float Vec3::dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 dudis::operator*(Vec3 vec, float scalar)
{
    vec *= scalar;
    return vec;
}

Vec3 dudis::operator*(float scalar, Vec3 vec)
{
    vec *= scalar;
    return vec;
}

Vec3 dudis::operator/(Vec3 vec, float scalar)
{
    vec /= scalar;
    return vec;
}
