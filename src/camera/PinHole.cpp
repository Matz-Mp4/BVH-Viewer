#include "../../include/camera/camera-types/PinHole.hpp" 
#include <cmath>


PinHole::PinHole(float fov, float ratio, float near, float far):
    fov(fov),
    asp_ratio(ratio),
    near(near),
    far(far)
{}

Matrix4 PinHole::projection_matrix(CoordSystem coord_system) const{

    float a =  2.0 * far * near  / (far - near);
    float b =  1.0;
    float c = -(far + near) / (far - near);

    if(coord_system == CoordSystem::RIGH_HAND) {
        a*= -1.0;
        b*= -1.0;
    }


    float scale = 1 / tan(fov * 0.5 * M_PI / 180);
    float m[16] = {
                    scale,     0, 0, 0,
                        0, scale, 0, 0,
                        0,     0, c, b,
                        0,     0, a, 0

                   };
    return Matrix4(m);
}
