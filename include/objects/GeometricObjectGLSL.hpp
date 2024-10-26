#pragma once
#include "../GLSL/export-data/ExportObject.hpp"
#include "../GLSL/utils/EBO.hpp"
#include "../GLSL/utils/VBO.hpp"
#include "../GLSL/utils/VAO.hpp"
#include "GeometricObject.hpp"
#include "IShape.hpp"
#include <GLFW/glfw3.h>

class GeometricObjectGLSL{
    public:
         GeometricObjectGLSL(const size_t& shader_id, const GeometricObject& object);
         GeometricObjectGLSL(const size_t& shader_id, ExportObject* export_object, IShape* shape);
         GeometricObjectGLSL(const size_t& shader_id, ExportObject* export_object, const GeometricObject& object);
         GeometricObjectGLSL() = default;

         //TODO: fix this *export_object
        ~GeometricObjectGLSL() = default; 

         void               export_mesh();
         void               delete_mesh();
         void     export_transformation();
         void           export_material();

         void change_export(ExportObject* _export_object);
         void change_shader(const size_t& _shader_id);

         void     handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height);
         void              draw();

    private:
        size_t             shader_id;
        GeometricObject       object;
        VAO                      vao;
        VBO                      vbo;
        EBO                      ebo;
        ExportObject*  export_object;
        double       last_x , last_y; // Last mouse position
        bool             is_dragging; // Is the right mouse button being held down
};
