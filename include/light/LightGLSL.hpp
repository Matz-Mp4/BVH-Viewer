#pragma once 

#include "GlobalAmbient.hpp"
/* #include "Directional.hpp" */
#include "PointLight.hpp"
#include "../GLSL/export-data/ExportLight.hpp"

class LightGLSL {
    public:
         LightGLSL(size_t _shader_id, const GlobalAmbient& _ambient_light, const PointLight& _point_light);
         LightGLSL(size_t _shader_id, ExportLight* _export_light, const GlobalAmbient& _ambient_light, const PointLight& _point_light);
         LightGLSL() = default;
        ~LightGLSL();

         void     export_ambient();
         void export_point_light();

         void      change_export(ExportLight* _export_light);
         void      change_shader(const size_t& _shader_id);

    private:
         size_t            shader_id;
         GlobalAmbient ambient_light;
         PointLight      point_light;
         ExportLight*   export_light;
};
