#pragma once 

#include "../../camera/Camera.hpp"

class ExportCamera{
    public: 
        virtual ~ExportCamera(){}
        virtual void export_projection(size_t shader_id, Camera& camera, TypeCamera* type_camera) = 0;
};
