#include "../../../../include/GLSL/export-data/export-camera/ExportProjection.hpp"
#include "../../../../include/GLSL/ShaderGLSL.hpp"

ExportProjection::ExportProjection(size_t shader_id, std::string projection_matrix):
    projection_matrix(projection_matrix),
    shader_id(shader_id)
{}

ExportProjection::ExportProjection(size_t shader_id):
    projection_matrix("cam_proj"),
    shader_id(shader_id)
{}


void ExportProjection::export_projection(Camera& camera, TypeCamera* type_camera) {

    Matrix4 projection = camera.compute_view_projection(type_camera, CoordSystem::RIGH_HAND);
    ShaderGLSL::set_matrix4(shader_id, projection_matrix, projection);
}

void ExportProjection::delete_projection(Camera& camera,TypeCamera* type_camera) {}
