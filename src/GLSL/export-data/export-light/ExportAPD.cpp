#include "../../../../include/GLSL/export-data/export-light/ExportAPD.hpp"
#include "../../../../include/GLSL/utils/ShaderGLSL.hpp"

ExportAPD::ExportAPD():
    ambient("ambient.color")
{
    point_light[0] = "point_light.position";
    point_light[1] = "point_light.color";
}
    
ExportAPD::ExportAPD(std::string _ambient, std::string _point_light[]):
     ambient(_ambient)
     //TODO: fix array initializer
     /* point_light(_point_light) */
{}


void ExportAPD::export_ambient(size_t shader_id, const GlobalAmbient &_ambient) {
    Color color = _ambient.get_color();
    ShaderGLSL::set_vector4(shader_id, ambient, Vector4(color.r, color.g, color.b, 1.0));

}


void ExportAPD::export_point_light(size_t shader_id, const PointLight &_point_light) {
    Color color = _point_light.get_color();
    ShaderGLSL::set_vector4(shader_id, point_light[0], Vector4(color.r, color.g, color.b, 1.0));
    ShaderGLSL::set_vector4(shader_id, point_light[1], _point_light.get_position());
}
