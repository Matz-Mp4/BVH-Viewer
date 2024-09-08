#pragma once
#include <vector>
#include "../math/Vector3.hpp"
#include "../objects/Vertex.hpp"

/**
  Represents a surface of a object by a list of points 
  that belongs to this surfaces
**/

//TODO: fan_triangle
class Mesh {
    public :
        Mesh() = default;
        /**
           Adds a new vertex in a mesh 
        **/
        void add_vertex(Vector3 position, Vector3 normal);

    private:
        std::vector<Vertex> vertices;
        std::vector<Vertex>  indices; //vertices indices
        size_t             triangles;
};
