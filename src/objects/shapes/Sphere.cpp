#include "../../../include/objects/shapes/Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector4 &center, const double radius)
    : center(center), radius(radius) {}


Mesh Sphere::generate_mesh() const {
   Mesh mesh;

    for (unsigned int i = 0; i < (u-1); i++) {
        for (unsigned int j = 0; j < (v-1); j++) {
            double theta = i * 180.0 / (u - 1.0);
            double phi =   j * 360.0 / (v - 1.0);

            double theta1 = (i + 1.0) * 180.0 / (u - 1.0);
            double phi1 =   (j + 1.0) * 360.0 / (v - 1.0);

            Vector4 p0 = position(radius, theta, phi);
            Vector4 n0(p0.x/radius, p0.y/radius, p0.z/radius);

            Vector4 p1 = position(radius, theta1, phi);
            Vector4 n1(p1.x/radius, p1.y/radius, p1.z/radius);

            Vector4 p2 = position(radius, theta1, phi1);
            Vector4 n2(p2.x/radius, p2.y/radius, p2.z/radius);

            Vector4 p3 = position(radius, theta, phi1);
            Vector4 n3(p3.x/radius, p3.y/radius, p3.z/radius);

            //First Triangle
            mesh.add_vertex(p0, n0);
            mesh.add_vertex(p1, n1);
            mesh.add_vertex(p3, n3);

            //TODO: maybe do need to add duplicates. Need to Check
            //Second Triangle
            mesh.add_vertex(p1, n1);
            mesh.add_vertex(p2, n2);
            mesh.add_vertex(p3, n3);
       }
    }

    return mesh;
}

Vector4 Sphere::position(double radius, double theta, double phi) {
    double x =  radius * std::sin(theta) * std::cos(phi);
    double y =  radius * std::cos(theta);
    double z = -radius * std::sin(theta) * std::sin(phi);

    return Vector4(x, y, z);
}
