#include "../GLSL/export-data/ExportCamera.hpp"
#include "Camera.hpp"
#include <GLFW/glfw3.h>
#pragma once 

class CameraGLSL {
    public:
        CameraGLSL(size_t id, const Camera& cam, TypeCamera* type_cam, const char* uniform_proj);
        CameraGLSL(ExportCamera* export_camera,  const Camera& cam, TypeCamera* type_cam, const char* uniform_proj);
        CameraGLSL() = default;
       ~CameraGLSL();

        void export_projection(); 
        void delete_projection();
        void handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height);
       

    private:
       float           sensitivity;
       bool            first_click;
       float                 speed;
       Camera                  cam;
       TypeCamera*    type_cam_ptr;
       std::string    uniform_proj;
       ExportCamera*  data_manager;



};
