#pragma once
#include "../IShape.hpp"
#include "../../math/Vector4.hpp"

class Cylinder : public IShape {
    public:
        Cylinder() = default;
       ~Cylinder() = default;
        Cylinder(const Vector4 &center, const float radius, const float height, unsigned int u = 20 ); // latitude

        Mesh generate_mesh() const override;

    private:
        // Compute the sphere position by spherical coordinates.
        // Theta and phi in degrees.
        static Vector4 position(float radius, float theta, float v_segment);
        unsigned int u; // latitude
        /* unsigned int v; // longitude */

        Vector4 center;
        float   radius;
        float   height;

};
