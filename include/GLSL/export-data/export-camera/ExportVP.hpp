#pragma once 

#include "../ExportCamera.hpp"

class ExportVP: public ExportCamera {
    public:
         ExportVP(size_t shader_id,  std::string view_matrix, std::string perspective_matrix);
         ExportVP(size_t shader_id);
         ExportVP() = default;
        ~ExportVP() = default;

         void export_projection(Camera& camera, TypeCamera* type_camera) override;
         void delete_projection(Camera& camera, TypeCamera* type_camera) override;

         void change_shader(size_t shader_id);

    private:
        std::string        view_matrix;
        std::string perspective_matrix;
        size_t               shader_id;

};
