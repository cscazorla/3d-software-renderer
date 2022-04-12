#ifndef CAMERA_H
#define CAMERA_H

#include "Color.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Mat4.h"

enum ProjectionType {
    ORTOGRAPHIC,
    PERSPECTIVE,
    ISOMETRIC,
    RAYTRACING
};

struct Camera {
    Vec3 position;
    Vec3 rotation;
    Vec3 direction;
    Vec3 target;

    Color background_color;

    // Raytracing
    int viewport_size;
    int projection_plane;

    // Projection
    Mat4 projection_matrix;
    ProjectionType projection_type;
    float zoom;

    // Light
    Vec3 light_direction;

    Camera();
    Camera(ProjectionType _projection);
    ~Camera() = default;

    Vec2 Project(Vec3 vertex);
    void SetTarget(Vec3 _target);
    Vec3 GetTarget(void);

    Vec3 FromCanvasToViewport(int x, int y, int width, int height);
};

#endif
