#include "../../include/camera/Camera.hpp" 

Camera::Camera(Vector4 eye , Vector4 direction , Vector4 up):
    eye(eye),
    direction(direction),
    up(up)
{
    this->compute_uvw();
}

void Camera::compute_uvw() {
    w = eye - direction;
    w.normalize();
    u = up | w;
    u.normalize();
    v = w | u;
}

Matrix4 Camera::look_at() {
    double data_orientation[16] =  {
            u.x, u.y, u.z, 0.0,
            v.x, v.y, v.z, 0.0,
            w.x, -(w.y), -(w.z), 0.0,
            0.0, 0.0, 0.0, 1.0
    };

    double data_translation[16] = {
            1.0, 0.0, 0.0, -eye.x,
            0.0, 1.0, 0.0, -eye.y,
            0.0, 0.0, 1.0, -eye.z,
            0.0, 0.0, 0.0, 1.0
    };
    Matrix4 orientation(data_orientation);
    Matrix4 translation(data_translation);

    return orientation * translation;

}

Matrix4 Camera::compute_view_projection(TypeCamera* type_cam) {
    return type_cam->projection_matrix() * this->look_at();
}
