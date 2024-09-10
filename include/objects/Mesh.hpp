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

        /**
           Adds a new vertex in a mesh 
        **/
        void add_vertex(Vector4 position, Vector4 normal);

    private:
        std::vector<Vertex> vertices;
        size_t             triangles;
};
