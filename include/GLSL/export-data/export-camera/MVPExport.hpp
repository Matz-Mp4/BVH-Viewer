#pragma once 

#include "../ExportCamera.hpp"

class ExportMVP: public ExportCamera {
    public:
         ExportMVP(size_t shader_id, std::string model_matrix, std::string view_matrix, std::string perspective_matrix);
        ~ExportMVP() = default;

         void export_projection(Camera& camera, TypeCamera* type_camera) override;
         void delete_projection(Camera& camera, TypeCamera* type_camera) override;

         void change_shader(size_t shader_id);

    private:
        std::string       model_matrix;
        std::string        view_matrix;
        std::string perspective_matrix;
        size_t               shader_id;

};
