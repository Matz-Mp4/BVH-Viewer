#pragma once
#include "../TypeCamera.hpp"

/**
    Represents a virtual model of a PinHole camera.
    - fov (field of view in the y-axis): the angle between the near plane and the far plane.
    - aspect: The aspect ratio of the viewport (width/height).
    - near and far: The distances from the camera to the near and far planes, respectively.
**/
class PinHole: public TypeCamera{
    public:
        PinHole(float fov, float ratio, float near, float far);
        Matrix4 projection_matrix(CoordSystem coord_system) const override;

    private:
        float       fov;
        float asp_ratio;
        float      near;
        float      far;
};
