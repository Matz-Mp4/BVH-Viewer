#pragma once 

class ObjectShader{
    public: 
        virtual void     export_mesh() = 0;
        virtual void     delete_mesh() = 0;
        virtual void export_material() = 0;
        virtual void delete_material() = 0;
};
