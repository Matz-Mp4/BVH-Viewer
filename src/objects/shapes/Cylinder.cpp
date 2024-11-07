#include "../../../include/objects/shapes/Cylinder.hpp"
#include "../../../third-party/glm/glm/trigonometric.hpp"
#include <cmath>

Cylinder::Cylinder(const Vector4 &center, const float radius, const float height,  unsigned int u  )
    : center(center), radius(radius), height(height), u(u){}


Mesh Cylinder::generate_mesh() const {
    Mesh mesh;
    std::vector<unsigned int> indices;

    // Step 1: Generate side vertices and indices
    for (unsigned int i = 0; i < u; i++) {
        float theta = i * 360.0f / u;
        float theta1 = (i + 1.0f) * 360.0f / u;

        Vector4 p_bottom = position(radius, theta, 0);            // Bottom ring vertex
        Vector4 p_top = position(radius, theta, height);          // Top ring vertex
        Vector4 p_bottom_next = position(radius, theta1, 0);      // Next bottom ring vertex
        Vector4 p_top_next = position(radius, theta1, height);    // Next top ring vertex

        // Normal vectors (normalized positions)
        Vector4 n_bottom = p_bottom.normalize();
        Vector4 n_top = p_top.normalize();
        Vector4 n_bottom_next = p_bottom_next.normalize();
        Vector4 n_top_next = p_top_next.normalize();

        // Add vertices to mesh
        unsigned int idx_bottom = mesh.add_vertex(p_bottom, n_bottom);
        unsigned int idx_top = mesh.add_vertex(p_top, n_top);
        unsigned int idx_bottom_next = mesh.add_vertex(p_bottom_next, n_bottom_next);
        unsigned int idx_top_next = mesh.add_vertex(p_top_next, n_top_next);

        // Side triangles
        indices.push_back(idx_bottom); indices.push_back(idx_bottom_next); indices.push_back(idx_top);
        indices.push_back(idx_bottom_next); indices.push_back(idx_top_next); indices.push_back(idx_top);
    }

    // Step 2: Generate top and bottom cap
    unsigned int center_bottom_idx = mesh.add_vertex(Vector4(0, 0, 0, 1), Vector4(0, 0, -1, 0));  // Center bottom vertex
    unsigned int center_top_idx = mesh.add_vertex(Vector4(0, 0, height, 1), Vector4(0, 0, 1, 0)); // Center top vertex

    for (unsigned int i = 0; i < u; i++) {
        float theta = i * 360.0f / u;
        float theta1 = (i + 1.0f) * 360.0f / u;

        Vector4 p_bottom = position(radius, theta, 0);            // Bottom ring vertex
        Vector4 p_top_next = position(radius, theta1, height);    // Next top ring vertex
        Vector4 p_bottom_next = position(radius, theta1, 0);      // Next bottom ring vertex
        Vector4 p_top = position(radius, theta, height);          // Top ring vertex

        // Add bottom cap triangle (center to two bottom vertices)
        unsigned int idx_bottom = mesh.add_vertex(p_bottom, Vector4(0, 0, -1, 0));  // Bottom normal facing down
        unsigned int idx_bottom_next = mesh.add_vertex(p_bottom_next, Vector4(0, 0, -1, 0));
        // Add top cap triangle (center to two top vertices)
        unsigned int idx_top = mesh.add_vertex(p_top, Vector4(0, 0, 1, 0));        // Top normal facing up
        unsigned int idx_top_next = mesh.add_vertex(p_top_next, Vector4(0, 0, 1, 0));

        indices.push_back(center_top_idx);
        indices.push_back(idx_top_next);
        indices.push_back(idx_top);

        indices.push_back(idx_bottom_next);
        indices.push_back(idx_bottom);
        indices.push_back(center_bottom_idx);


    }

    mesh.indices = indices;
    return mesh;
}
Vector4 Cylinder::position(float radius, float theta, float v_segment) {
    theta = glm::radians(theta);
    return Vector4(
         radius * sin(theta),
         radius * cos(theta),
         v_segment,
         1.0
       );
}
