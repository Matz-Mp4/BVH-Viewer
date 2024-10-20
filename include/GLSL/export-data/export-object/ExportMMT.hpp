#pragma once

#include <string>
#include "../ExportObject.hpp"

class ExportMMT: public ExportObject{
    public:
         ExportMMT(size_t shader_id, const std::string transformation, const std::string& material);
         ExportMMT(size_t shader_id);
         ExportMMT() = default;
        ~ExportMMT() = default;

         void           export_mesh(const Mesh &mesh, VAO& vao,VBO& vbo, EBO& ebo) override; 
         void           delete_mesh(VAO& vao,VBO& vbo, EBO& ebo) override; 
         void       export_material(const Material &material) override;
         void export_transformation(const Matrix4 &transformation) override;
        

    private:
        /** Material: 
         *  - Color        [0]
         *  - ambient      [1]
         *  - diffuse      [2]
         *  - specular     [3]
         *  - spec_expoent [4]
        **/
        std::string     material[5];
        size_t            shader_id;
        std::string  transformation;



};


