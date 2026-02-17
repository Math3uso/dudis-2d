#pragma once

namespace dudis
{
    class Vec4
    {
    public:
        float x = 0.f;
        float y = 0.f;
        float z = 0.f;
        float w = 0.f;

        Vec4() = default;
        Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        Vec4(float value) : x(value), y(value), z(value), w(value) {};

        bool operator==(const Vec4 &other) const;
        bool operator!=(const Vec4 &other) const;

        Vec4 operator+(const Vec4 &other) const;
        Vec4 operator-(const Vec4 &other) const;
        Vec4 &operator+=(const Vec4 &other);
        Vec4 &operator-=(const Vec4 &other);

        Vec4 &operator*=(float scalar);
        Vec4 &operator/=(float scalar);

        Vec4 operator-() const;

        float length() const;
        float lengthSquared() const;
        Vec4 normalized() const;

        static float dot(const Vec4 &a, const Vec4 &b);
    };

    Vec4 operator*(Vec4 vec, float scalar);
    Vec4 operator*(float scalar, Vec4 vec);
    Vec4 operator/(Vec4 vec, float scalar);
}
