#include "Vec4.h"
#include <math.h>
#include <iostream>

Vec4::Vec4(): x(0.0), y(0.0), z(0.0), w(0.0) {}

Vec4::Vec4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

std::ostream& operator <<(std::ostream& os, const Vec4& v)
{
    os << '(' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
    return os;
}

void Vec4::Add(const Vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
}

void Vec4::Sub(const Vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
}

void Vec4::Scale(const float n) {
    x *= n;
    y *= n;
    z *= n;
    w *= n;
}

float Vec4::Magnitude() const {
    return sqrtf(x * x + y * y + z * z + w * w);
}

float Vec4::MagnitudeSquared() const {
    return (x * x + y * y + z * z + w * w);
}

Vec4& Vec4::Normalize() {
    float length = Magnitude();
    if (length != 0.0) {
        x /= length;
        y /= length;
        z /= length;
        w /= length;
    }
    return *this;
}

Vec4 Vec4::UnitVector() const {
    Vec4 result = Vec4();
    float length = Magnitude();
    if (length != 0.0) {
        result.x = x / length;
        result.y = y / length;
        result.z = z / length;
        result.w = w / length;
    }
    return result;
}

float Vec4::Dot(Vec4 v) {
    return (x * v.x) + (y * v.y) + (z * v.z) + (w * v.w);
}

Vec4 Vec4::Lerp(Vec4 a, Vec4 b, float t) {
    Vec4 diff = b - a;
    diff *= t;
    Vec4 result = a + diff;
    return result;
}

Vec3 Vec4::TransformIntoVec3() {
    Vec3 result = Vec3(x, y, z);
    return result;
}

Vec4& Vec4::operator = (const Vec4& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

bool Vec4::operator == (const Vec4& v) const {
    return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vec4::operator != (const Vec4& v) const {
    return !(*this == v);
}

Vec4 Vec4::operator + (const Vec4& v) const {
    Vec4 result;
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    result.w = y + v.w;
    return result;
}

Vec4 Vec4::operator - (const Vec4& v) const {
    Vec4 result;
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    result.w = w - v.w;
    return result;
}

Vec4 Vec4::operator * (const float n) const {
    Vec4 result;
    result.x = x * n;
    result.y = y * n;
    result.z = z * n;
    result.w = w * n;
    return result;
}

Vec4 Vec4::operator / (const float n) const {
    Vec4 result;
    result.x = x / n;
    result.y = y / n;
    result.z = z / n;
    result.w = w / n;
    return result;
}

Vec4& Vec4::operator += (const Vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}

Vec4& Vec4::operator -= (const Vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}

Vec4& Vec4::operator *= (const float n) {
    x *= n;
    y *= n;
    z *= n;
    w *= n;
    return *this;
}

Vec4& Vec4::operator /= (const float n) {
    x /= n;
    y /= n;
    z /= n;
    w /= n;
    return *this;
}

Vec4 Vec4::operator - () {
    Vec4 result;
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;
    result.w = w * -1;
    return result;
}
