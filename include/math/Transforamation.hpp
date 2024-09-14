#pragma once
#include "Matrix4.hpp"

class Transformation {
    public:
        static Matrix4 translation(float x, float y, float z) ;
        static Matrix4     scaling(float x, float y, float z) ;
        static Matrix4  rotation_x(float angle);
        static Matrix4  rotation_y(float angle);
        static Matrix4  rotation_z(float angle);
};
