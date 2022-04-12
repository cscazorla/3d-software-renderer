#include "Vec3.h"
#include <math.h>
#include <iostream>

Vec3::Vec3(): x(0.0), y(0.0), z(0.0) {}

Vec3::Vec3(float x, float y, float z): x(x), y(y), z(z) {}

std::ostream& operator <<(std::ostream& os, const Vec3& v)
{
    os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    return os;
}

void Vec3::Add(const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

void Vec3::Sub(const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

void Vec3::Scale(const float n) {
    x *= n;
    y *= n;
    z *= n;
}

float Vec3::Magnitude() const {
    return sqrtf(x * x + y * y + z * z);
}

float Vec3::MagnitudeSquared() const {
    return (x * x + y * y + z * z);
}

Vec3& Vec3::Normalize() {
    float length = Magnitude();
    if (length != 0.0) {
        x /= length;
        y /= length;
        z /= length;
    }
    return *this;
}

Vec3 Vec3::UnitVector() const {
    Vec3 result = Vec3();
    float length = Magnitude();
    if (length != 0.0) {
        result.x = x / length;
        result.y = y / length;
        result.z = z / length;
    }
    return result;
}

float Vec3::Dot(const Vec3& v) const {
    return (x * v.x) + (y * v.y) + (z * v.z);
}

Vec3 Vec3::Cross(const Vec3& v) const {
    Vec3 result = Vec3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
    return result;
}

Vec3 Vec3::Lerp(Vec3 a, Vec3 b, float t) {
    Vec3 diff = b - a;
    diff *= t;
    Vec3 result = a + diff;
    return result;
}

Vec4 Vec3::TransformIntoVec4() {
    Vec4 result = Vec4(x, y, z, 1);
    return result;
}

Vec3& Vec3::operator = (const Vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

bool Vec3::operator == (const Vec3& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool Vec3::operator != (const Vec3& v) const {
    return !(*this == v);
}

Vec3 Vec3::operator + (const Vec3& v) const {
    Vec3 result;
    result.x = x + v.x;
    result.y = y + v.y;
    result.z = z + v.z;
    return result;
}

Vec3 Vec3::operator - (const Vec3& v) const {
    Vec3 result;
    result.x = x - v.x;
    result.y = y - v.y;
    result.z = z - v.z;
    return result;
}

Vec3 Vec3::operator * (const float n) const {
    Vec3 result;
    result.x = x * n;
    result.y = y * n;
    result.z = z * n;
    return result;
}

Vec3 Vec3::operator / (const float n) const {
    Vec3 result;
    result.x = x / n;
    result.y = y / n;
    result.z = z / n;
    return result;
}

Vec3& Vec3::operator += (const Vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vec3& Vec3::operator -= (const Vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vec3& Vec3::operator *= (const float n) {
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

Vec3& Vec3::operator /= (const float n) {
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

Vec3 Vec3::operator - () {
    Vec3 result;
    result.x = x * -1;
    result.y = y * -1;
    result.z = z * -1;
    return result;
}
