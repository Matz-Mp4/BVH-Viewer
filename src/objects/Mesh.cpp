#include "../../include/objects/Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices)
    : vertices(vertices) {}

void Mesh::add_vertex(Vector4 position, Vector4 normal) {
    vertices.push_back(Vertex(position, normal));
}

void Mesh::add_indice(unsigned int indice) {
    indices.push_back(indice);
}

void Mesh::update_num_triangles() {
    triangles = sizeof(indices) / sizeof(unsigned int);
}
