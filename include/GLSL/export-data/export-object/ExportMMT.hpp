#pragma once

#include <string>
#include "../ExportObject.hpp"

class ExportMMT: public ExportObject{
    public:
         ExportMMT(const std::string transformation, const std::string& material);
         ExportMMT();
        ~ExportMMT() = default;

         void           export_mesh(const Mesh &mesh, VAO& vao,VBO& vbo, EBO& ebo) override; 
         void           delete_mesh(VAO& vao,VBO& vbo, EBO& ebo) override; 
         void       export_material(size_t shader_id, const Material &material) override;
         void export_transformation(size_t shader_id, const Matrix4 &transformation) override;
        

    private:
        /** Material: 
         *  - Color        [0]
         *  - ambient      [1]
         *  - diffuse      [2]
         *  - specular     [3]
         *  - spec_expoent [4]
        **/
        std::string     material[5];
        std::string  transformation;
};


