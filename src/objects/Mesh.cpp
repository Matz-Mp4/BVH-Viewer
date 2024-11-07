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

std::vector<Vector4> Mesh::centroids() const {
    std::vector<Vector4> centroids;
    Vector4 centroid_with_index;
    int num_triangles = vertices.size() / 3;

    for(int i = 0; i < num_triangles; i++) {
        Vector4 p0 = Vector4(vertices[i * 3 + 0].position);
        Vector4 p1 = Vector4(vertices[i * 3 + 1].position);
        Vector4 p2 = Vector4(vertices[i * 3 + 2].position);

        centroid_with_index.x = (p0.x + p1.x + p2.x) / 3.0;
        centroid_with_index.y = (p0.y + p1.y + p2.y) / 3.0;
        centroid_with_index.z = (p0.z + p1.z + p2.z) / 3.0;
        centroid_with_index.w = (float)i;

        centroids.push_back(centroid_with_index);
    }
    return centroids;


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
