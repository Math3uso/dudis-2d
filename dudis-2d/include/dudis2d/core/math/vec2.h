#pragma once

namespace dudis
{
    class Vec2
    {
    public:
        float x = 0.f;
        float y = 0.f;

        Vec2() = default;
        Vec2(float x, float y) : x(x), y(y) {}
        Vec2(float value) : x(value), y(value) {};

        bool operator==(const Vec2 &other) const;
        bool operator!=(const Vec2 &other) const;

        Vec2 operator+(const Vec2 &other) const;
        Vec2 operator-(const Vec2 &other) const;
        Vec2 &operator+=(const Vec2 &other);
        Vec2 &operator-=(const Vec2 &other);

        Vec2 &operator*=(float scalar);
        Vec2 &operator/=(float scalar);

        Vec2 operator-() const;

        float length() const;
        float lengthSquared() const;
        Vec2 normalized() const;

        static float dot(const Vec2 &a, const Vec2 &b);
    };

    Vec2 operator*(Vec2 vec, float scalar);
    Vec2 operator*(float scalar, Vec2 vec);
    Vec2 operator/(Vec2 vec, float scalar);
}
