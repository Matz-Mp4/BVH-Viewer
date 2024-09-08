#pragma once
#include "../math/Matrix4.hpp"

class TypeCamera {
    virtual Matrix4 projection_matrix() const = 0;
};
