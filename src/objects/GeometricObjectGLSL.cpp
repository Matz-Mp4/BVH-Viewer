#include "../../include/objects/GeometricObjectGLSL.hpp"

GeometricObjectGLSL::GeometricObjectGLSL(size_t id, const GeometricObject& object, const std::string& uniform_material) :
    shader_id(id),
    object(object),
    uniform_material(uniform_material)
{}

GeometricObjectGLSL::GeometricObjectGLSL(size_t id, IShape* shape, const std::string& uniform_material) :
    shader_id(id),
    uniform_material(uniform_material)
{
    object = object.with_shape(shape);
}

void GeometricObjectGLSL::export_mesh() {
    vao.Bind();
	// Generates Vertex Buffer Object and links it to vertices
    vbo = VBO(object.get_vertices());
	// Generates Element Buffer Object and links it to indices
    ebo = EBO(object.get_indices());    
    //Vertex Position data to layout = 0
    vao.LinkAttrib(vbo, 0, 4, GL_FLOAT, sizeof(Vertex), (void*)0 );
    //Vertex Normal to layout = 1
    vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    //Unbind all to prevent accidentally modifying them
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

}

void GeometricObjectGLSL::delete_mesh() {
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}


//TODO: implementation of export_material
void GeometricObjectGLSL::export_material() {
}

void GeometricObjectGLSL::delete_material() {
}

void GeometricObjectGLSL::draw() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, object.get_indices().size(), GL_UNSIGNED_INT, 0);
       
}

