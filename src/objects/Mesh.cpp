#include "../../include/objects/Mesh.hpp"

void Mesh::add_vertex(Vector3 vertice) {
    vertices.push_back(vertice);
}

//TODO: fan_triangle
/*
void Mesh::fan_triangulation(std::vector<Vector3> vertices) {
    std::vector<Vector3> triangles;
    Vector3 triangle;

    for(int i = 1; i < vertices.size() - 1; i++) {
        triangle(vertices
    }
}*/
