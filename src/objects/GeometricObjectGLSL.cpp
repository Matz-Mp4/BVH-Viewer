#include "../../include/objects/GeometricObjectGLSL.hpp"
#include "../../include/GLSL/export-data/export-object/ExportMMT.hpp"

GeometricObjectGLSL::GeometricObjectGLSL(const size_t& shader_id, const GeometricObject& object) :
    object(object),
    shader_id(shader_id)
{
    export_object = new ExportMMT();
}

GeometricObjectGLSL::GeometricObjectGLSL(const size_t& shader_id, ExportObject* export_object, const GeometricObject& object):
    export_object(export_object),
    shader_id(shader_id),
    object(object)
{}

GeometricObjectGLSL::GeometricObjectGLSL(const size_t& shader_id, ExportObject* export_object, IShape* shape) :
    export_object(export_object),
    shader_id(shader_id)
{
    object = object.with_shape(shape);
}

void GeometricObjectGLSL::export_mesh() {
    export_object->export_mesh(object.get_mesh(), vao, vbo, ebo);
}

void GeometricObjectGLSL::delete_mesh() {
    export_object->delete_mesh(vao, vbo, ebo);
    
}

void GeometricObjectGLSL::export_material() {
    export_object->export_material(shader_id, object.get_material());
}

void GeometricObjectGLSL::export_transformation() {
    export_object->export_transformation(shader_id, object.get_transformation());
}



void GeometricObjectGLSL::change_export(ExportObject* _export_object) {
    this->export_object = _export_object;
}


 void GeometricObjectGLSL::change_shader(const size_t& _shader_id) {
     shader_id = _shader_id;
 }

void GeometricObjectGLSL::draw() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, object.get_indices().size(), GL_UNSIGNED_INT, 0);
       
}

