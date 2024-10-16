#pragma once 

class CameraShader{
    public: 
        virtual void export_projection() = 0;
        virtual void delete_projection() = 0;
};
