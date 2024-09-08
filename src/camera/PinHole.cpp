#include "../../include/camera/camera-types/PinHole.hpp" 


PinHole::PinHole(double fov, double ratio, double near, double far):
    fov(fov),
    asp_ratio(ratio),
    near(near),
    far(far)
{}

//TODO
void PinHole::projection_matrix() const{
}
