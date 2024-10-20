#include "../../../../include/GLSL/export-data/export-camera/ExportProjection.hpp"
#include "../../../../include/GLSL/utils/ShaderGLSL.hpp"

ExportProjection::ExportProjection(std::string projection_matrix):
    projection_matrix(projection_matrix)
{}

ExportProjection::ExportProjection():
    projection_matrix("cam_proj")
{}


void ExportProjection::export_projection(size_t shader_id, Camera& camera, TypeCamera* type_camera) {

    Matrix4 projection = camera.compute_view_projection(type_camera, CoordSystem::RIGH_HAND);
    ShaderGLSL::set_matrix4(shader_id, projection_matrix, projection);
}

