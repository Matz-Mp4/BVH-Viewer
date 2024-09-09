#include "../../include/camera/camera-types/PinHole.hpp" 
#include <cmath>


PinHole::PinHole(double fov, double ratio, double near, double far):
    fov(fov),
    asp_ratio(ratio),
    near(near),
    far(far)
{}

Matrix4 PinHole::projection_matrix() const{
    double m[16] = {
                    1 / (asp_ratio * tan(fov / 2)), 0, 0, 0,
                    0, 1 / tan(fov / 2), 0, 0,
                    0, 0, (far + near) / (far - near), (2 * far * near) / (far - near),
                    0, 0, -1, 0
                   };
    return Matrix4(m);
}
