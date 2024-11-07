#pragma once
#include <vector>

#include "../math/Vector4.hpp"
#include "../objects/Vertex.hpp"

class Mesh {
    public :
         Mesh() = default;
        ~Mesh() = default;
         Mesh(std::vector<Vertex> vertices);

        // Add a vertex to the mesh and return its index 
        unsigned int        add_vertex(Vector4 position);
        unsigned int        add_vertex(Vector4 position, Vector4 normal);
        void                add_indice(unsigned int indice);
        void      update_num_triangles();
        // Compute centroids of each triangle
        std::vector<Vector4> centroids() const;

        friend std::ostream& operator<<(std::ostream& stream, const Mesh& mesh); 

        std::vector<Vertex>      vertices;
        std::vector<unsigned int> indices;
        size_t                  triangles;
};
