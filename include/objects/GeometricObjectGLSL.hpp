#pragma once

#include "../GLSL/export-data/ExportObject.hpp"
#include "../GLSL/utils/EBO.hpp"
#include "../GLSL/utils/VBO.hpp"
#include "../GLSL/utils/VAO.hpp"
#include "GeometricObject.hpp"
#include "IShape.hpp"

class GeometricObjectGLSL{
    public:
         GeometricObjectGLSL(size_t id, const GeometricObject& object);
         GeometricObjectGLSL(ExportObject* export_object, IShape* shape);
         GeometricObjectGLSL(ExportObject* export_object, const GeometricObject& object);
         GeometricObjectGLSL() = default;
         //TODO: fix this *export_object
        ~GeometricObjectGLSL() = default; 

         void               export_mesh();
         void               delete_mesh();
         void     export_transformation();
         void           export_material();

         void change_export(ExportObject* _export_object);

         void draw();

    private:
        GeometricObject       object;
        VAO                      vao;
        VBO                      vbo;
        EBO                      ebo;
        ExportObject*  export_object;
};
