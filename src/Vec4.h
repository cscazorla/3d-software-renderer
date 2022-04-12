#ifndef VEC4_H
#define VEC4_H

// To avoid a cyclic dependency between Vec3 and Vec4
// This is due to the TransformIntoVec3
struct Vec4;
#include "Vec3.h"
#include <iostream>

struct Vec4 {
    float x;
    float y;
    float z;
    float w;

    Vec4();
    Vec4(float x, float y, float z, float w);
    ~Vec4() = default;

    void Add(const Vec4& v);
    void Sub(const Vec4& v);
    void Scale(const float n);

    float Magnitude() const;
    float MagnitudeSquared() const;

    Vec4& Normalize();
    Vec4 UnitVector() const;

    float Dot(Vec4 v);

    static Vec4 Lerp(Vec4 a, Vec4 b, float t);

    Vec3 TransformIntoVec3();

    friend std::ostream& operator<<(std::ostream& os, const Vec4& v);

    Vec4& operator = (const Vec4& v);        // v1 = v2
    bool operator == (const Vec4& v) const;  // v1 == v2
    bool operator != (const Vec4& v) const;  // v1 != v2
    
    Vec4 operator + (const Vec4& v) const;   // v1 + v2
    Vec4 operator - (const Vec4& v) const;   // v1 - v2
    Vec4 operator * (const float n) const;   // v1 * n
    Vec4 operator / (const float n) const;   // v1 / n
    Vec4 operator - ();                      // -v1

    Vec4& operator += (const Vec4& v);       // v1 += v2
    Vec4& operator -= (const Vec4& v);       // v1 -= v2
    Vec4& operator *= (const float n);       // v1 *= n
    Vec4& operator /= (const float n);       // v1 /= n
};

#endif
