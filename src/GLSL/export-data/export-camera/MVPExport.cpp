#include "../../../../include/GLSL/export-data/export-camera/MVPExport.hpp"
#include "../../../../include/GLSL/ShaderGLSL.hpp"

ExportMVP::ExportMVP(size_t shader_id, std::string model_matrix, std::string view_matrix, std::string perspective_matrix):
    model_matrix(model_matrix),
    view_matrix(view_matrix),
    perspective_matrix(perspective_matrix),
    shader_id(shader_id)
{}


void ExportMVP::export_projection(Camera& camera, TypeCamera* type_camera) {

    //TODO: change this 
    Matrix4 view_proj = camera.compute_view_projection(type_camera, CoordSystem::RIGH_HAND);
    ShaderGLSL::set_matrix4(shader_id, "cameraProj", view_proj);



}

void ExportMVP::delete_projection(Camera& camera,TypeCamera* type_camera) {}
