#include "../../include/objects/Mesh.hpp"

void Mesh::add_vertex(Vector4 position, Vector4 normal) {
    vertices.push_back(Vertex(position, normal));
}
