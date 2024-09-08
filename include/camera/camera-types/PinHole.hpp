#pragma once
#include "../TypeCamera.hpp"

/**
    Represents a virtual model of a PinHole camera.
    - fov (field of view in the y-axis): the angle between the near plane and the far plane.
    - aspect: The aspect ratio of the viewport (width/height).
    - near and far: The distances from the camera to the near and far planes, respectively.
**/
class PinHole: TypeCamera{
    public:
        PinHole(double fov, double ratio, double near, double far);
        //TODO
        void projection_matrix() const override;

    private:
        double       fov;
        double asp_ratio;
        double      near;
        double      far;
};
