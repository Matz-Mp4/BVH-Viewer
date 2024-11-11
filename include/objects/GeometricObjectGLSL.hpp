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

         void           export_mesh();
         void           delete_mesh();
         void export_transformation();
         void       export_material();
         void         change_export(ExportObject* _export_object);
         void         change_shader(const size_t& _shader_id);

         void        handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height);
         void                 draw();

        
        GeometricObjectGLSL             with_shape(const IShape* shape);
        GeometricObjectGLSL    with_transformation(const Matrix4& transformation);
        GeometricObjectGLSL          with_material(const Material& _material);
        GeometricObjectGLSL             with_color(float r, float g, float b);
        GeometricObjectGLSL              with_mesh(const Mesh& _mesh);
        void                             transform(Matrix4& _transformation);

        Material                       get_material() const;
        Mesh                               get_mesh() const;
        Matrix4                  get_transformation() const;
        std::vector<Vertex>            get_vertices() const;
        std::vector<unsigned int>       get_indices() const;

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
