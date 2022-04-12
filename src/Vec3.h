#ifndef VEC3_H
#define VEC3_H

// To avoid a cyclic dependency between Vec3 and Vec4
// This is due to the TransformIntoVec4
struct Vec3;
#include "Vec4.h"
#include <iostream>

struct Vec3 {
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x, float y, float z);
    ~Vec3() = default;

    void Add(const Vec3& v);
    void Sub(const Vec3& v);
    void Scale(const float n);

    float Magnitude() const;
    float MagnitudeSquared() const;

    Vec3& Normalize();
    Vec3 UnitVector() const;

    float Dot(const Vec3& v) const;
    Vec3 Cross(const Vec3& v) const;

    static Vec3 Lerp(Vec3 a, Vec3 b, float t);

    Vec4 TransformIntoVec4();

    friend std::ostream& operator<<(std::ostream& os, const Vec3& v);

    Vec3& operator = (const Vec3& v);        // v1 = v2
    bool operator == (const Vec3& v) const;  // v1 == v2
    bool operator != (const Vec3& v) const;  // v1 != v2
    
    Vec3 operator + (const Vec3& v) const;   // v1 + v2
    Vec3 operator - (const Vec3& v) const;   // v1 - v2
    Vec3 operator * (const float n) const;   // v1 * n
    Vec3 operator / (const float n) const;   // v1 / n
    Vec3 operator - ();                      // -v1

    Vec3& operator += (const Vec3& v);       // v1 += v2
    Vec3& operator -= (const Vec3& v);       // v1 -= v2
    Vec3& operator *= (const float n);       // v1 *= n
    Vec3& operator /= (const float n);       // v1 /= n
};

#endif
