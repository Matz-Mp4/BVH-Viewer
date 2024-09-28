#include "../../../include/objects/shapes/Sphere.hpp"
#include <cmath>
#include <glm/trigonometric.hpp>


Sphere::Sphere(const Vector4 &center, const float radius, unsigned int u , unsigned int v )
    : center(center), radius(radius), u(u), v(v) {}


Mesh Sphere::generate_mesh() const {
   Mesh mesh;
   std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < (u-1); i++) {
        for (unsigned int j = 0; j < (v-1); j++) {
            float theta = i * 180.0 / (u - 1.0);
            float phi =   j * 360.0 / (v - 1.0);
            float theta1 = (i + 1.0) * 180.0 / (u - 1.0);
            float phi1 =   (j + 1.0) * 360.0 / (v - 1.0);

            Vector4 p0 = position(radius, theta, phi);
            Vector4 n0 = p0.normalize();

            Vector4 p1 = position(radius, theta1, phi);
            Vector4 n1 = p1.normalize();

            Vector4 p2 = position(radius, theta1, phi1);
            Vector4 n2 =  p2.normalize();

            Vector4 p3 = position(radius, theta, phi1);
            Vector4 n3 = p3.normalize();

            unsigned int idx0 = mesh.add_vertex(p0, n0);
            unsigned int idx1 = mesh.add_vertex(p1, n1);
            unsigned int idx2 = mesh.add_vertex(p2, n2);
            unsigned int idx3 = mesh.add_vertex(p3, n3);

            indices.push_back(idx0);
            indices.push_back(idx1);
            indices.push_back(idx3);

            indices.push_back(idx1);
            indices.push_back(idx2);
            indices.push_back(idx3);
                 

       }
    }

    mesh.indices = indices;
    return mesh;
}

Vector4 Sphere::position(float radius, float theta, float phi) {
    theta = glm::radians(theta);
    phi = glm::radians(phi);
    return Vector4(
        radius * sin(theta) * cos(phi),
        radius * cos(theta),
        radius * sin(theta) * sin(phi)
       );
}
