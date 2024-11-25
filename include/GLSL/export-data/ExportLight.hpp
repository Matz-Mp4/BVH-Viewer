#pragma once 

#include "../../light/GlobalAmbient.hpp"
#include "../../light/PointLight.hpp"

class ExportLight {
    public:
         virtual            ~ExportLight() {};
         virtual void     export_ambient(size_t shader_id, const GlobalAmbient &_ambient) = 0;
         virtual void export_point_light(size_t shader_id, const PointLight &_point_light) = 0;
};


