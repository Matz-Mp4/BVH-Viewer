#pragma once
#include "../math/Matrix4.hpp"
#include "CoordinateSystem.hpp"

class TypeCamera {
    public: 
        virtual Matrix4 projection_matrix(CoordSystem coord_system) const = 0;
};
