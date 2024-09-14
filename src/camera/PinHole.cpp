#include "../../include/camera/camera-types/PinHole.hpp" 
#include <cmath>


PinHole::PinHole(float fov, float ratio, float near, float far):
    fov(fov),
    asp_ratio(ratio),
    near(near),
    far(far)
{}

Matrix4 PinHole::projection_matrix() const{
    float tan_fov_half = (float)(tan(fov / 2));
    float m[16] = {
                    1.0f / (asp_ratio * tan_fov_half), 0, 0, 0,
                    0, 1 / tan_fov_half, 0, 0,
                    0, 0, (far + near) / (far - near), (2 * far * near) / (far - near),
                    0, 0, -1, 0
                   };
    return Matrix4(m);
}
