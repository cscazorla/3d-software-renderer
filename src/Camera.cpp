#include "Camera.h"
#include "Mat4.h"
#include <iostream>

Camera::Camera(): projection_type(PERSPECTIVE), zoom(200) {}

Camera::Camera(ProjectionType _projection): projection_type(_projection) {}

Vec2 Camera::Project(Vec3 vertex) {
    Vec2 result;

    if(projection_type == PERSPECTIVE) {
        // To Do: Check we are not dividing by 0
        result.x = (zoom * vertex.x) / vertex.z;
        result.y = (zoom * vertex.y) / vertex.z;
    }

    if(projection_type == ORTOGRAPHIC) {
        result.x = vertex.x;
        result.y = vertex.y;
    }

    if(projection_type == ISOMETRIC) {
        result.x = (vertex.x - vertex.y) * zoom;
        result.y = (vertex.x + vertex.y) * 0.5 * zoom;
    }

    return result;
}

void Camera::SetTarget(Vec3 _target) {
    target = _target;
}

Vec3 Camera::GetTarget(void) {
    Mat4 rotation_matrix = Mat4::CreateRotationXYZ(rotation.x, rotation.y, rotation.z);
    Vec4 camera_direction = rotation_matrix * target.TransformIntoVec4();
    direction = camera_direction.TransformIntoVec3();
    return position + direction;
}

Vec3 Camera::FromCanvasToViewport(int x, int y, int width, int height) {
    Vec3 viewport_pixel = Vec3(
        (x * viewport_size/(float)width),
        (y * viewport_size/(float)height),
        projection_plane
    );
    return viewport_pixel - position;
}
