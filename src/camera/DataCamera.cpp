#include "../../include/camera/DataCamera.hpp" 

DataCamera::DataCamera(Vector3 eye , Vector3 look_at , Vector3 up):
    eye(eye),
    look_at(look_at),
    up(up)
{
    this->compute_uvw();
}

void DataCamera::compute_uvw() {
    w = eye - look_at;
    w.normalize();
    u = up | w;
    u.normalize();
    v = w | u;
}
