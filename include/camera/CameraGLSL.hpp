#include "../GLSL/export-data/CameraShader.hpp"
#include "Camera.hpp"
#include <GLFW/glfw3.h>
#pragma once 

class CameraGLSL : public CameraShader{
    public:
        CameraGLSL(size_t id, const Camera& cam, TypeCamera* type_cam, const char* uniform_proj);
        CameraGLSL() = default;
       ~CameraGLSL();

        void export_projection() override; 
        void delete_projection() override;
        void handle_inputs(GLFWwindow* window, unsigned int width, unsigned int height);
       

    private:
       size_t         shader_id;
       float        sensitivity;
       bool         first_click;
       float              speed;
       Camera               cam;
       TypeCamera* type_cam_ptr;
       std::string uniform_proj;



};
