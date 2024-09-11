#pragma once

#include "../IShape.hpp"
#include "../../math/Vector4.hpp"

class Sphere : public IShape {
    public:
        Vector4 center;
        double radius;

        unsigned int u; // latitude
        unsigned int v; // longitude

        Sphere() = default;
        ~Sphere() = default;

        Sphere(const Vector4 &center, const double radius);

        Mesh generate_mesh() const override;

    private:
        // Compute the sphere position by spherical coordinates.
        // Theta and phi in degrees.
        static Vector4 position(double radius, double theta, double phi);
};
