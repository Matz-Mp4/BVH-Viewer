#include "../../include/camera/Camera.hpp" 

Camera::Camera(Vector4 eye , Vector4 direction , Vector4 up):
    eye(eye),
    direction(direction),
    up(up)
{
    /* this->compute_othor_bases(); */
}

void Camera::compute_othor_bases(CoordSystem coord_system) {

    if ( coord_system == CoordSystem::LEFT_HAND)
        forward = direction - eye;
    else if (coord_system == CoordSystem::RIGH_HAND)
        forward = eye - direction;

    forward.normalize();
    right = up | forward;
    right.normalize();
    new_up = forward | right;
}

Matrix4 Camera::look_at(CoordSystem coord_system) {
    compute_othor_bases(coord_system);

    float a = right * eye ;
    float b = new_up * eye ;
    float c = forward * eye ;

    if(coord_system == CoordSystem::RIGH_HAND) {
        a*= -1.0;
        b*= -1.0;
        c*= -1.0;
    }
     

    float  view []= {
      right.x, new_up.x, forward.x, 0,
      right.y, new_up.y, forward.y, 0,
      right.z, new_up.z, forward.z, 0,
            a,        b,         c, 1.0
    };


    return Matrix4(view);
}

Matrix4 Camera::compute_view_projection(TypeCamera* type_cam, CoordSystem coord_system) {
    return  look_at(coord_system) * type_cam->projection_matrix(coord_system) ;
}
