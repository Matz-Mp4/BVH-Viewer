#include "../../include/light/LightGLSL.hpp"
#include "../../include/GLSL/export-data/export-light/ExportAPD.hpp"

LightGLSL::LightGLSL(size_t _shader_id, const GlobalAmbient& _ambient_light, const PointLight& _point_light):
    shader_id(_shader_id),
    ambient_light(_ambient_light),
    point_light(_point_light)
{
    export_light = new ExportAPD();
}


LightGLSL::LightGLSL(size_t _shader_id, ExportLight* _export_light, const GlobalAmbient& _ambient_light, const PointLight& _point_light):
    shader_id(_shader_id),
    ambient_light(_ambient_light),
    point_light(_point_light),
    export_light(_export_light)
{}

LightGLSL::~LightGLSL() {
    if(export_light != nullptr) {
        delete export_light;
        export_light = nullptr;
    }
}

void LightGLSL::export_ambient() {
    export_light->export_ambient(shader_id, ambient_light);
}


void LightGLSL::export_point_light() {
    export_light->export_point_light(shader_id, point_light);
}

void LightGLSL::change_shader(const size_t& _shader_id) {
     shader_id = _shader_id;
}

void LightGLSL::change_export(ExportLight* _export_light) {
     if (export_light != nullptr) {
         delete export_light;
     }
     export_light = _export_light;
}

