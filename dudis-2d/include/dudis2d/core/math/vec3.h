#pragma once

namespace dudis
{
    class Vec3
    {
    public:
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;

        Vec3() = default;
        Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vec3(float value) : x(value), y(value), z(value) {};

        bool operator==(const Vec3 &other) const;
        bool operator!=(const Vec3 &other) const;

        Vec3 operator+(const Vec3 &other) const;
        Vec3 operator-(const Vec3 &other) const;
        Vec3 &operator+=(const Vec3 &other);
        Vec3 &operator-=(const Vec3 &other);

        Vec3 &operator*=(float scalar);
        Vec3 &operator/=(float scalar);

        Vec3 operator-() const;

        float length() const;
        float lengthSquared() const;
        Vec3 normalized() const;

        static float dot(const Vec3 &a, const Vec3 &b);
    };

    Vec3 operator*(Vec3 vec, float scalar);
    Vec3 operator*(float scalar, Vec3 vec);
    Vec3 operator/(Vec3 vec, float scalar);
}
