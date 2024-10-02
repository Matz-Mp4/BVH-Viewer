#include "../include/objects/shapes/ModelLoader.hpp"
#include "../../../third-party/happly/happly.h"

#include <iostream>
#include <vector>

ModelLoader::ModelLoader(const std::string& filepath)
    : filepath(filepath) {}

Mesh ModelLoader::generate_mesh() const {
    if (filepath.substr(filepath.find_last_of(".") + 1) == "ply") {
        return load_ply(this->filepath);
    } else if (filepath.substr(filepath.find_last_of(".") + 1) == "obj") {
        return load_obj(this->filepath);
    } else {
        std::cerr << "Formato de arquivo nao suportado!" << std::endl;
        return Mesh();
    }
}

Mesh ModelLoader::load_ply(const std::string& filepath) const {
    // Construct a data object by reading from file
    happly::PLYData plyIn(filepath);

    // Get data from object
    std::vector<std::array<double, 3>> vertices = plyIn.getVertexPositions();
    std::vector<std::vector<size_t>> indices = plyIn.getFaceIndices<size_t>();

    Mesh mesh;
    for (const auto& vertex : vertices) {
        mesh.add_vertex(Vector4(vertex[0], vertex[1], vertex[2], 1.0));
    }

    for (const auto& indice : indices) {
        Vector4 edge1 =  mesh.vertices[indice[1]].position -  mesh.vertices[indice[0]].position;
        Vector4 edge2 =  mesh.vertices[indice[2]].position -  mesh.vertices[indice[0]].position;
        Vector4 normal = (edge2 | edge1).normalize();

        mesh.vertices[indice[0]].normal = normal;
        mesh.vertices[indice[1]].normal = normal;
        mesh.vertices[indice[2]].normal = normal;

        mesh.add_indice(indice[0]);
        mesh.add_indice(indice[1]);
        mesh.add_indice(indice[2]);
    }

    return mesh;
}

Mesh ModelLoader::load_obj(const std::string& filepath) const {
}
