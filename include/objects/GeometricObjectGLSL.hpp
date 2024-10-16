#pragma once

#include "../GLSL/export-data/ObjectShader.hpp"
#include "../GLSL/EBO.hpp"
#include "../GLSL/VBO.hpp"
#include "../GLSL/VAO.hpp"
#include "GeometricObject.hpp"
#include "IShape.hpp"

class GeometricObjectGLSL: public ObjectShader {
    public:
         GeometricObjectGLSL(size_t id, const GeometricObject& object, const std::string& uniform_material);
         GeometricObjectGLSL(size_t id, IShape* shape, const std::string& uniform_material);
         GeometricObjectGLSL() = default;
        ~GeometricObjectGLSL() = default; 

         void     export_mesh() override;
         void     delete_mesh() override;
         void export_material() override;
         void delete_material() override;

         void draw();

    private:
        size_t             shader_id;
        std::string uniform_material;
        GeometricObject       object;
        VAO                      vao;
        VBO                      vbo;
        EBO                      ebo;





};
