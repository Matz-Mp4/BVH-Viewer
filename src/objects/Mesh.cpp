#include "../../include/objects/Mesh.hpp"
#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices)
    : vertices(vertices) {}

unsigned int Mesh::add_vertex(Vector4 position) {
    vertices.push_back(Vertex(position, Vector4(0.0)));
    return vertices.size() - 1;
}

unsigned int Mesh::add_vertex(Vector4 position, Vector4 normal) {
    vertices.push_back(Vertex(position, normal));
    return vertices.size() - 1;
}

void Mesh::add_indice(unsigned int indice) {
    indices.push_back(indice);
}

void Mesh::update_num_triangles() {
    triangles = sizeof(indices) / sizeof(unsigned int);
}

std::ostream& operator<<(std::ostream& stream, const Mesh& mesh) {
    stream << "Vertices  = (Postion, Vertices) = {" << std::endl;
    for(int i = 0; i < mesh.vertices.size(); i++ ) {
        stream << "   [" << mesh.vertices[i].position << ", " << mesh.vertices[i].normal << "]," << std::endl;
    }
    stream << " } " << std::endl;

    std::cout<< "Indices = {" << std::endl;
    for(int i = 0; i < mesh.indices.size(); i++ ) {
        stream << "   [" << mesh.indices[i]<<"]," <<std::endl;
    }
    stream << " } " << std::endl;
    return stream;
}
