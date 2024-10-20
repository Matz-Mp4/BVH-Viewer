#pragma once 

#include "../../objects/Mesh.hpp"
#include "../../material/Material.hpp"
#include "../../math/Matrix4.hpp"
#include "../utils/VAO.hpp"
#include "../utils/EBO.hpp"
#include "../utils/VBO.hpp"

class ExportObject{
    public: 
         virtual void           export_mesh(const Mesh &mesh, VAO& vao,VBO& vbo, EBO& ebo) = 0; 
         virtual void           delete_mesh(VAO& vao,VBO& vbo, EBO& ebo) = 0; 
         virtual void       export_material(const Material &material) = 0;
         virtual void export_transformation(const Matrix4 &transformation) = 0;

};
