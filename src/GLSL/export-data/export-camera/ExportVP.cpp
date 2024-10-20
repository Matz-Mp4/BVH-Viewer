#include "../../../../include/GLSL/export-data/export-camera/ExportVP.hpp"
#include "../../../../include/GLSL/utils/ShaderGLSL.hpp"

ExportVP::ExportVP(std::string view_matrix, std::string perspective_matrix):
    view_matrix(view_matrix),
    perspective_matrix(perspective_matrix)
{}

ExportVP::ExportVP():
    view_matrix("v_matrix"),
    perspective_matrix("p_matrix")
{}


void ExportVP::export_projection(size_t shader_id, Camera& camera, TypeCamera* type_camera) {
    Matrix4 perspective_proj = type_camera->projection_matrix(CoordSystem::RIGH_HAND);
    Matrix4 view_proj = camera.look_at(CoordSystem::RIGH_HAND);
    ShaderGLSL::set_matrix4(shader_id, view_matrix, view_proj);
    ShaderGLSL::set_matrix4(shader_id, perspective_matrix, perspective_proj);
}

