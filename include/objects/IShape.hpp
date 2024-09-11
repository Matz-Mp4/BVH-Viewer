#pragma once

#include "Mesh.hpp"

class IShape {
    protected:
        virtual Mesh generate_mesh() const = 0;
};
