#pragma once
#include <vector>
#include "../math/Vector4.hpp"

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
        void add_vertex(Vector4 vertice);
    private:
        std::vector<Vector4> vertices;
        std::vector<Vector4>  normals; //average normal at each vertice
        std::vector<Vector4>  indices; //vertices indices
        size_t              n_indices;

};



