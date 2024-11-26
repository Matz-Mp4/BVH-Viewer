#include "../GLSL/export-data/ExportCamera.hpp"
#include "Camera.hpp"
/* #include <GLFW/glfw3.h> */
#include "glfw3.h"
#pragma once 

class CameraGLSL {
    public:
        CameraGLSL(size_t shader_id, const Camera& cam, TypeCamera* type_cam);
        CameraGLSL(size_t shader_id, ExportCamera* export_camera,  const Camera& cam, TypeCamera* type_cam);
        CameraGLSL() = default;
       ~CameraGLSL();

        void export_projection(); 
        void     handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height);
        void     change_export(ExportCamera* _export_camera);
        void     change_shader(const size_t& _shader_id);

        Vector4   get_position() const;
        Vector4  get_direction() const;
        Vector4         get_up() const;

    private:
       size_t            shader_id;
       float           sensitivity;
       bool            first_click;
       float                 speed;
       Camera                  cam;
       TypeCamera*    type_cam_ptr;
       ExportCamera* export_camera;
       float          x_pos, y_pos;
       float        x_prev, y_prev;



};
