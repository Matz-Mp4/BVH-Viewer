#include "../../include/objects/Mesh.hpp"

void Mesh::add_vertex(Vector3 position, Vector3 normal) {
    vertices.push_back(Vertex(position, normal));
}
