#include "../include/objects/ObjectLoader.hpp"
#include "../../third-party/happly/happly.h"

#include <iostream>
#include <vector>

ObjectLoader::ObjectLoader(const std::string& filepath)
    : filepath(filepath) {}

Mesh ObjectLoader::generate_mesh() const {
    if (filepath.substr(filepath.find_last_of(".") + 1) == "ply") {
        return load_ply(this->filepath);
    } else if (filepath.substr(filepath.find_last_of(".") + 1) == "obj") {
        return load_obj(this->filepath);
    } else {
        std::cerr << "Formato de arquivo nao suportado!" << std::endl;
        return Mesh();
    }
}

Mesh ObjectLoader::load_ply(const std::string& filepath) const {
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
        for (const auto& x : indice) {
            mesh.add_indice(x);
        }
    }

    return mesh;
}

Mesh ObjectLoader::load_obj(const std::string& filepath) const {
}
