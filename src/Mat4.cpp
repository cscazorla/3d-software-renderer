#include "Mat4.h"
#include <math.h>
#include <iostream>
#include <vector>

Mat4::Mat4() {
    Zero();
}


Mat4::Mat4(const Mat4& m) {
    *this = m;
}

Mat4::~Mat4() {}

void Mat4::Zero() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = 0.0f;
}

Mat4 Mat4::Transpose() const {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[j][i] = m[i][j];
    return result;
}

Mat4 Mat4::CreateIdentity() {
    Mat4 result = Mat4();
    for (int i = 0; i < 4; i++)
        result.m[i][i] = 1;
    return result;
}

Mat4 Mat4::CreateScale(float sx, float sy, float sz) {
    Mat4 result = Mat4::CreateIdentity();
    result.m[0][0] = sx;
    result.m[1][1] = sy;
    result.m[2][2] = sz;
	return result;
}

Mat4 Mat4::CreateTranslate(float tx, float ty, float tz) {
    Mat4 result = Mat4::CreateIdentity();
    result.m[0][3] = tx;
    result.m[1][3] = ty;
    result.m[2][3] = tz;
    return result;
}

// Creates a rotation matrix around the X axis
// | 1  0  0  0 |
// | 0  c -s  0 |
// | 0  s  c  0 |
// | 0  0  0  1 |
Mat4 Mat4::CreateRotationX(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 result = Mat4::CreateIdentity();
    result.m[1][1] = c;
    result.m[1][2] = -s;
    result.m[2][1] = s;
    result.m[2][2] = c;
    return result;
}

// Creates a rotation matrix around the Y axis
// |  c  0  s  0 |
// |  0  1  0  0 |
// | -s  0  c  0 |
// |  0  0  0  1 |
Mat4 Mat4::CreateRotationY(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 result = Mat4::CreateIdentity();
    result.m[0][0] = c;
    result.m[0][2] = s;
    result.m[2][0] = -s;
    result.m[2][2] = c;
    return result;
}

// Creates a rotation matrix around the Z axis
// | c -s  0  0 |
// | s  c  0  0 |
// | 0  0  1  0 |
// | 0  0  0  1 |
Mat4 Mat4::CreateRotationZ(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    Mat4 result = Mat4::CreateIdentity();
    result.m[0][0] = c;
    result.m[0][1] = -s;
    result.m[1][0] = s;
    result.m[1][1] = c;
    return result;
}

Mat4 Mat4::CreateRotationXYZ(float angle_x, float angle_y, float angle_z) {
    Mat4 rotation_x = Mat4::CreateRotationX(angle_x);
    Mat4 rotation_y = Mat4::CreateRotationY(angle_y);
    Mat4 rotation_z = Mat4::CreateRotationZ(angle_z);
    Mat4 rotation = rotation_x * rotation_y * rotation_z;
    return rotation;
}

Mat4 Mat4::CreatePerspective(float fov, float aspect, float znear, float zfar) {
    // | (h/w)*1/tan(fov/2)             0              0                 0 |
    // |                  0  1/tan(fov/2)              0                 0 |
    // |                  0             0     zf/(zf-zn)  (-zf*zn)/(zf-zn) |
    // |                  0             0              1                 0 |
    Mat4 result = Mat4();
    result.m[0][0] = aspect * (1 / tan(fov / 2));
    result.m[1][1] = 1 / tan(fov / 2);
    result.m[2][2] = zfar / (zfar - znear);
    result.m[2][3] = (-zfar * znear) / (zfar - znear);
    result.m[3][2] = 1.0;
    return result;
}

Mat4 Mat4::CreateLookAt(Vec3 eye, Vec3 target, Vec3 up) {
    // | x.x   x.y   x.z  -dot(x,eye) |
    // | y.x   y.y   y.z  -dot(y,eye) |
    // | z.x   z.y   z.z  -dot(z,eye) |
    // |   0     0     0            1 |

    // Compute forward (z), right (x) and up (y) vectors
    Vec3 z = (target - eye).Normalize();
    Vec3 x = up.Cross(z).Normalize();
    Vec3 y = z.Cross(x).Normalize();

    // Create matrix
    Mat4 result = Mat4::CreateIdentity();
    result.m[0][0] = x.x;
    result.m[0][1] = x.y;
    result.m[0][2] = x.z;
    result.m[0][3] = -x.Dot(eye);
    result.m[1][0] = y.x;
    result.m[1][1] = y.y;
    result.m[1][2] = y.z;
    result.m[1][3] = -y.Dot(eye);
    result.m[2][0] = z.x;
    result.m[2][1] = z.y;
    result.m[2][2] = z.z;
    result.m[2][3] = -z.Dot(eye);
    return result;
}

std::ostream& operator<<(std::ostream& os, const Mat4& matrix) {
    for (int i = 0; i < 4; i++) {
        os << '|' << '\t';
        for (int j = 0; j < 4; j++) {
            os << ' ' << std::fixed << matrix.m[i][j] << '\t';
        }
        os << '|' << std::endl;
    }
    return os;
}

void Mat4::operator = (const Mat4 &other) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = other.m[i][j];
}

Vec4 Mat4::operator * (Vec4 v) {
    Vec4 result = Vec4();
    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    result.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    result.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;
	return result;
}

Mat4 Mat4::operator * (const Mat4 &other) const {
    Mat4 result = Mat4::CreateIdentity();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.m[i][j] = m[i][0] * other.m[0][j] + m[i][1] * other.m[1][j] + m[i][2] * other.m[2][j] + m[i][3] * other.m[3][j];
        }
    }
    return result;
}
