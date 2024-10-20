#include "../../../../include/GLSL/export-data/export-object/ExportMMT.hpp"
#include "../../../../include/GLSL/utils/ShaderGLSL.hpp"

ExportMMT::ExportMMT(size_t shader_id, const std::string transformation, const std::string& material):
    shader_id(shader_id),
    transformation(transformation)
    /* material(material) */
{}

ExportMMT::ExportMMT(size_t shader_id):
    shader_id(shader_id),
    transformation("m_matrix")
{
    material[0] =  "mateiral.color"; 
    material[1] =  "material.k_amb"; 
    material[2] =  "material.k_dif"; 
    material[3] =  "material.k_spec";
    material[4] =  "material.exp";
};


void ExportMMT::export_mesh(const Mesh &mesh, VAO& vao,VBO& vbo, EBO& ebo){
    vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
    vbo = VBO(mesh.vertices);
	// Generates Element Buffer Object and links it to indices
    ebo = EBO(mesh.indices);    
    //Vertex Position data to layout = 0
    vao.LinkAttrib(vbo, 0, 4, GL_FLOAT, sizeof(Vertex), (void*)0 );
    //Vertex Normal to layout = 1
    vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    //Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();


}    
void ExportMMT::delete_mesh(VAO& vao, VBO& vbo, EBO& ebo){
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}    

//TODO: Create this get functions
void ExportMMT::export_material(const Material &material){
    /* ShaderGLSL::set_float(shader_id, this->material[0], material.get_color()); */
    ShaderGLSL::set_float(shader_id, this->material[0], material.get_ambient());
    ShaderGLSL::set_float(shader_id, this->material[0], material.get_diffuse());
    ShaderGLSL::set_float(shader_id, this->material[0], material.get_specular());
    ShaderGLSL::set_float(shader_id, this->material[0], material.get_expoent());
} 

void ExportMMT::export_transformation(const Matrix4& transformation){
    ShaderGLSL::set_matrix4(shader_id, this->transformation, transformation);
} 
