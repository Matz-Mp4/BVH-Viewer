#pragma once
#include <vector>
#include "../math/Vector3.hpp"

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
        void add_vertex(Vector3 vertice);

        /**
           Simple way to triangulate a polygon by choosing a vertex and drawing edges 
           to all of the other vertices of the polygon
        **/
        void fan_triangulation();

    private:
        std::vector<Vector3> vertices;
        std::vector<Vector3>  normals; //average normal at each vertice
        std::vector<Vector3>  indices; //vertices indices
        size_t              n_indices;

};



