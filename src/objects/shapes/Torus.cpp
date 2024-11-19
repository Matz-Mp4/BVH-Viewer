#include "../../../include/objects/shapes/Torus.hpp"
#include "../../../include/math/Utils.hpp"
#include <cmath>


Torus::Torus(const Vector4 &center, const float _r_torus, float _r_tube, unsigned int u , unsigned int v )
    : center(center), r_torus(_r_torus), r_tube(_r_tube), u(u), v(v) {}


Mesh Torus::generate_mesh() const {
   Mesh mesh;
   std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < (u-1); i++) {
        for (unsigned int j = 0; j < (v-1); j++) {
            float theta = i * 360.0 / (u - 1.0);
            float phi =   j * 360.0 / (v - 1.0);
            float theta1 = (i + 1.0) * 360.0 / (u - 1.0);
            float phi1 =   (j + 1.0) * 360.0 / (v - 1.0);


            Vector4 p0 = position(r_torus,r_tube, theta, phi);
            Vector4 p1 = position(r_torus, r_tube, theta1, phi);
            Vector4 p2 = position(r_torus,r_tube, theta1, phi1);
            Vector4 p3 = position(r_torus, r_tube, theta, phi1);

            Vector4 temp1= Vector4(p2.x - p0.x, p2.y - p0.y, p2.z - p0.z);
            Vector4 temp2 = Vector4(p3.x - p1.x, p3.y - p1.y, p3.z - p1.z);
            Vector4 n = (temp1 | temp2).normalize();


            unsigned int idx0 = mesh.add_vertex(p0, n);
            unsigned int idx1 = mesh.add_vertex(p1, n);
            unsigned int idx2 = mesh.add_vertex(p2, n);
            unsigned int idx3 = mesh.add_vertex(p3, n);

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

Vector4 Torus::position(float r_torus, float r_tube, float u, float v) {
    u = math_utils::radians(u);
    v = math_utils::radians(v);
    return Vector4(
        (r_torus + r_tube * cos(v)) * cos(u) ,
        (r_tube * sin(v)),
       -(r_torus + r_tube * cos(v)) * sin(u) ,
         1.0
       );
}
