#include "../../../include/objects/shapes/Sphere.hpp"
#include <cmath>

Sphere::Sphere(const Vector4 &center, const float radius, unsigned int u , unsigned int v )
    : center(center), radius(radius), u(u), v(v) {}


Mesh Sphere::generate_mesh() const {
   Mesh mesh;

    for (unsigned int i = 0; i < (u-1); i++) {
        for (unsigned int j = 0; j < (v-1); j++) {
            float theta = i * 180.0 / (u - 1.0);
            float phi =   j * 360.0 / (v - 1.0);
            float theta1 = (i + 1.0) * 180.0 / (u - 1.0);
            float phi1 =   (j + 1.0) * 360.0 / (v - 1.0);

            Vector4 p0 = position(radius, theta, phi);
            Vector4 n0(p0.x/radius, p0.y/radius, p0.z/radius);

            Vector4 p1 = position(radius, theta1, phi);
            Vector4 n1(p1.x/radius, p1.y/radius, p1.z/radius);

            Vector4 p2 = position(radius, theta1, phi1);
            Vector4 n2(p2.x/radius, p2.y/radius, p2.z/radius);

            Vector4 p3 = position(radius, theta, phi1);
            Vector4 n3(p3.x/radius, p3.y/radius, p3.z/radius);

            unsigned int i0 = i * v + j;
            unsigned int i1 = (i + 1) * v + j;
            unsigned int i2 = (i + 1) * v + (j + 1);
            unsigned int i3 = i * v + (j + 1);

            // First Triangle (p0, p1, p3)
            mesh.add_indice(i0);
            mesh.add_indice(i1);
            mesh.add_indice(i3);

            // Second Triangle (p1, p2, p3)
            mesh.add_indice(i1);
            mesh.add_indice(i2);
            mesh.add_indice(i3);
       }
    }

    return mesh;
}

Vector4 Sphere::position(float radius, float theta, float phi) {
    float x =  radius * std::sin(theta) * std::cos(phi);
    float y =  radius * std::cos(theta);
    float z = -radius * std::sin(theta) * std::sin(phi);

    return Vector4(x, y, z);
}
