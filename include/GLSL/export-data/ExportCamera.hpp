#pragma once 

#include "../../camera/Camera.hpp"

class ExportCamera{
    public: 
        virtual ~ExportCamera(){}
        virtual void export_projection(Camera& camera, TypeCamera* type_camera) = 0;
        virtual void delete_projection(Camera& camera, TypeCamera* type_camera) = 0;
};
