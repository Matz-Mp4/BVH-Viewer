#pragma once
#include <vector>

#include "../math/Vector4.hpp"
#include "../objects/Vertex.hpp"

/**
  Represents a surface of a object by a list of points
  that belongs to this surfaces
**/

//TODO: fan_triangle
class Mesh {
    public :
        Mesh() = default;
        ~Mesh() = default;

        Mesh(std::vector<Vertex> vertices);

       void add_vertex(Vector4 position, Vector4 normal);
       void add_indice(unsigned int indice);
       void update_num_triangles();

    private:
        std::vector<Vertex>      vertices;
        std::vector<unsigned int> indices;
        size_t                  triangles;
};
