#include "../../../../include/GLSL/export-data/export-camera/ExportVP.hpp"
#include "../../../../include/GLSL/utils/ShaderGLSL.hpp"

ExportVP::ExportVP(size_t shader_id, std::string view_matrix, std::string perspective_matrix):
    view_matrix(view_matrix),
    perspective_matrix(perspective_matrix),
    shader_id(shader_id)
{}

ExportVP::ExportVP(size_t shader_id):
    view_matrix("v_matrix"),
    perspective_matrix("p_matrix"),
    shader_id(shader_id)
{}


void ExportVP::export_projection(Camera& camera, TypeCamera* type_camera) {
    Matrix4 perspective_proj = type_camera->projection_matrix(CoordSystem::RIGH_HAND);
    Matrix4 view_proj = camera.look_at(CoordSystem::RIGH_HAND);
    ShaderGLSL::set_matrix4(shader_id, view_matrix, view_proj);
    ShaderGLSL::set_matrix4(shader_id, perspective_matrix, perspective_proj);
}

void ExportVP::delete_projection(Camera& camera,TypeCamera* type_camera) {}
