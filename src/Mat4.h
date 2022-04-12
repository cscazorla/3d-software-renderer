#ifndef MAT4_H
#define MAT4_H

#include "Vec4.h"
#include <iostream>

struct Mat4 {
    float m[4][4];

    Mat4();
    Mat4(const Mat4& m);
    ~Mat4();

    void Zero();
    Mat4 Transpose() const;
    static Mat4 CreateIdentity();
    static Mat4 CreateScale(float sx, float sy, float sz);
    static Mat4 CreateTranslate(float tx, float ty, float tz);
    static Mat4 CreateRotationX(float angle);
    static Mat4 CreateRotationY(float angle);
    static Mat4 CreateRotationZ(float angle);
    static Mat4 CreateRotationXYZ(float angle_x, float angle_y, float angle_z);
    static Mat4 CreatePerspective(float fov, float aspect, float znear, float zfar);
    static Mat4 CreateLookAt(Vec3 eye, Vec3 target, Vec3 up);

    friend std::ostream& operator<<(std::ostream& os, const Mat4& m);
    void operator = (const Mat4 &other);          // m1 = m2
    Mat4 operator * (const Mat4 &other) const;    // m = m1 * m2
    Vec4 operator * (Vec4 v);                     // v = m1 * v
};

#endif
