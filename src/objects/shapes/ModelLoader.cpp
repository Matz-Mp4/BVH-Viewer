#include "../include/objects/shapes/ModelLoader.hpp"
#include "../../../third-party/happly/happly.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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
#include <fstream>
#include <sstream>
#include <unordered_map>

Mesh ModelLoader::load_obj(const std::string& filepath) const {
    Mesh mesh;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Could not open the file: " << filepath << std::endl;
        return mesh;
    }

    std::string line;
    std::vector<Vector4> temp_vertices;
    std::vector<Vector4> temp_normals;
    bool has_normals = false;

    // Map to store unique vertex/normal pairs and their mesh indices
    std::unordered_map<std::string, unsigned int> vertex_normal_map;

    auto generate_key = [](size_t v_idx, size_t n_idx) -> std::string {
        return std::to_string(v_idx) + "/" + std::to_string(n_idx);
    };

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string prefix;
        ss >> prefix;

        if (prefix == "v") {
            // Vertex position
            double x, y, z;
            ss >> x >> y >> z;
            temp_vertices.push_back(Vector4(x, y, z, 1.0));
        } else if (prefix == "vn") {
            // Vertex normal
            has_normals = true;
            double nx, ny, nz;
            ss >> nx >> ny >> nz;
            temp_normals.push_back(Vector4(nx, ny, nz, 0.0));
        } else if (prefix == "f") {
            // Face indices
            std::string vertex_info;
            std::vector<unsigned int> face_indices;

            while (ss >> vertex_info) {
                std::replace(vertex_info.begin(), vertex_info.end(), '/', ' ');
                std::istringstream vs(vertex_info);
                size_t vertex_index, tex_index, normal_index = 0;
                
                vs >> vertex_index;
                if (vs.peek() == ' ') vs.ignore(); // Skip texture coord index
                if (vs >> normal_index) { --normal_index; } // Adjust to 0-based index
                
                --vertex_index; // Convert to 0-based index
                std::string key = generate_key(vertex_index, has_normals ? normal_index : 0);

                if (vertex_normal_map.find(key) == vertex_normal_map.end()) {
                    // Add unique vertex/normal to the mesh
                    unsigned int mesh_index;
                    if (has_normals && normal_index < temp_normals.size()) {
                        mesh_index = mesh.add_vertex(temp_vertices[vertex_index], temp_normals[normal_index].normalize());
                    } else {
                        mesh_index = mesh.add_vertex(temp_vertices[vertex_index]);
                    }
                    vertex_normal_map[key] = mesh_index;
                }

                // Store the index for the face
                face_indices.push_back(vertex_normal_map[key]);
            }

            // Add indices for the triangle (assumes triangular faces)
            if (face_indices.size() == 3) {
                for (size_t i = 0; i < 3; ++i) {
                    mesh.add_indice(face_indices[i]);
                }
            } else {
                std::cerr << "Non-triangular faces are not supported" << std::endl;
            }
        }
    }

    file.close();

    // If normals are not provided, calculate them
    if (!has_normals) {
        // Initialize vertex normals to zero
        std::vector<Vector4> vertex_normals(mesh.vertices.size(), Vector4(0.0, 0.0, 0.0, 0.0));

        // Calculate face normals and accumulate them to each vertex of the face
        for (size_t i = 0; i < mesh.indices.size(); i += 3) {
            unsigned int idx0 = mesh.indices[i];
            unsigned int idx1 = mesh.indices[i + 1];
            unsigned int idx2 = mesh.indices[i + 2];

            Vector4 v0 = mesh.vertices[idx0].position;
            Vector4 v1 = mesh.vertices[idx1].position;
            Vector4 v2 = mesh.vertices[idx2].position;

            Vector4 edge1 = v1 - v0;
            Vector4 edge2 = v2 - v0;
            Vector4 face_normal = (edge1 | edge2).normalize();

            vertex_normals[idx0] = vertex_normals[idx0] + face_normal;
            vertex_normals[idx1] = vertex_normals[idx1] + face_normal;
            vertex_normals[idx2] = vertex_normals[idx2] + face_normal;
        }

        // Normalize all accumulated normals and assign them to each vertex
        for (size_t i = 0; i < mesh.vertices.size(); ++i) {
            mesh.vertices[i].normal = vertex_normals[i].normalize();
        }
    }

    mesh.update_num_triangles();
    return mesh;
}


