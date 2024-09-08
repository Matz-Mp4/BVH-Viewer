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

//TODO
Matrix4 Camera::look_at() {

}
