#pragma once 

#include "../ExportCamera.hpp"

class ExportVP: public ExportCamera {
    public:
         ExportVP(std::string view_matrix, std::string perspective_matrix);
         ExportVP();
        ~ExportVP() = default;

         void export_projection(size_t shader_id, Camera& camera, TypeCamera* type_camera) override;

    private:
        std::string        view_matrix;
        std::string perspective_matrix;

};
