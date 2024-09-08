#include "../../include/camera/DataCamera.hpp" 

DataCamera::DataCamera(Vector3 eye , Vector3 direction , Vector3 up):
    eye(eye),
    direction(direction),
    up(up)
{
    this->compute_uvw();
}

void DataCamera::compute_uvw() {
    w = eye - direction;
    w.normalize();
    u = up | w;
    u.normalize();
    v = w | u;
}

//TODO
void look_at() {
}
