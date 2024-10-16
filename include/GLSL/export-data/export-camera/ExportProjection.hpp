#pragma once 

#include "../ExportCamera.hpp"

class ExportProjection: public ExportCamera {
    public:
         ExportProjection(size_t shader_id, std::string projection_matrix);
         ExportProjection(size_t shader_id);
        ~ExportProjection() = default;

         void export_projection(Camera& camera, TypeCamera* type_camera) override;
         void delete_projection(Camera& camera, TypeCamera* type_camera) override;

         void change_shader(size_t shader_id);

    private:
        std::string  projection_matrix;
        size_t               shader_id;

};
