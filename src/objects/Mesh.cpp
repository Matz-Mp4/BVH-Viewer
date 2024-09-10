#include "../../include/objects/Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices)
    : vertices(vertices) {}

void Mesh::add_vertex(Vector4 position, Vector4 normal) {
    vertices.push_back(Vertex(position, normal));
}
