#pragma once
#include "Mesh.hpp"
#include "../material/Material.hpp"
#include "IShape.hpp"

class GeometricObject {
    public :
        GeometricObject() = default;
       ~GeometricObject() = default;
        GeometricObject(const IShape* shape, const Material& _material);
        GeometricObject(const Mesh& _mesh, const Material& _material);
        
        GeometricObject     with_shape(const IShape* shape);
        GeometricObject  with_material(const Material& _material);
                
    private: 
        Material material;
        Mesh        mesh;

};
