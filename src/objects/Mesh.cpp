#include "../../include/objects/Mesh.hpp"

void Mesh::add_vertex(Vector4 vertice) {
    vertices.push_back(vertice);
}

//TODO: fan_triangle
/*
void Mesh::fan_triangulation(std::vector<Vector4> vertices) {
    std::vector<Vector4> triangles;
    Vector4 triangle;

    for(int i = 1; i < vertices.size() - 1; i++) {
        triangle(vertices
    }
}*/
