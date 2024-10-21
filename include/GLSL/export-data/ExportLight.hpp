#pragma once 

#include "../../light/GlobalAmbient.hpp"
#include "../../light/PointLight.hpp"
/* #include "../../light/Directional.hpp" */

class ExportLight {
    public:
        ~ExportLight() {};
         virtual void     export_ambient(size_t shader_id, const GlobalAmbient &_ambient) = 0;
         virtual void export_point_light(size_t shader_id, const PointLight &_point_light) = 0;
         //TODO 
         /* virtual void export_directional(size_t shader_id, const PointLight &_point_light) = 0; */
};


