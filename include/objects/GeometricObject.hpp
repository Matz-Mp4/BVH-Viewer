#pragma once

#include "../material/Material.hpp"
#include "../math/Matrix4.hpp"
#include "IShape.hpp"
#include "Mesh.hpp"

class GeometricObject {
    public :
        GeometricObject() = default;
        GeometricObject(const IShape* shape, const Material& _material);
        GeometricObject(const IShape* shape, const Material& _material, const Matrix4& _transfomation);
        GeometricObject(const Mesh& _mesh, const Material& _material, const Matrix4& _transformation);
       ~GeometricObject() = default;
        
        GeometricObject             with_shape(const IShape* shape);
        GeometricObject    with_transformation(const Matrix4& transformation);
        GeometricObject          with_material(const Material& _material);

        Material                       get_material() const;
        Mesh                               get_mesh() const;
        Matrix4                  get_transformation() const;
        std::vector<Vertex>            get_vertices() const;
        std::vector<unsigned int>       get_indices() const;


        friend std::ostream& operator<<(std::ostream& stream, const GeometricObject& object); 

        void transform(Matrix4& _transformation);
                
    private: 
        Material      material;
        Mesh              mesh;
        Matrix4 transformation;

};
