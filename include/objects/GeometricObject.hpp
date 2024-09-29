#pragma once

#include "../material/Material.hpp"
#include "IShape.hpp"
#include "Mesh.hpp"

class GeometricObject {
    public :
        GeometricObject() = default;
        GeometricObject(const IShape* shape, const Material& _material);
       ~GeometricObject() = default;
        GeometricObject(const Mesh& _mesh, const Material& _material);
        
        GeometricObject     with_shape(const IShape* shape);
        GeometricObject  with_material(const Material& _material);

        Material                 get_material() const;
        std::vector<Vertex>      get_vertices() const;
        std::vector<unsigned int> get_indices() const;
                
    private: 
        Material material;
        Mesh        mesh;

};
