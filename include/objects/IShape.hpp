#pragma once

#include "Mesh.hpp"

class IShape {
    public:
        virtual Mesh generate_mesh() const = 0;
};
