#pragma once 

#include "../ExportCamera.hpp"

class ExportProjection: public ExportCamera {
    public:
         ExportProjection(std::string projection_matrix);
         ExportProjection();
        ~ExportProjection() = default;

         void export_projection(size_t shader_id, Camera& camera, TypeCamera* type_camera) override;

    private:
        std::string  projection_matrix;
        size_t               shader_id;

};
