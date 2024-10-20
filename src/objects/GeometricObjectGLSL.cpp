#include "../../include/objects/GeometricObjectGLSL.hpp"
#include "../../include/GLSL/export-data/export-object/ExportMMT.hpp"

GeometricObjectGLSL::GeometricObjectGLSL(size_t id, const GeometricObject& object) :
    object(object)
{
    export_object = new ExportMMT(id);
}

GeometricObjectGLSL::GeometricObjectGLSL(ExportObject* export_object, const GeometricObject& object):
    export_object(export_object),
    object(object)
{}

GeometricObjectGLSL::GeometricObjectGLSL(ExportObject* export_object, IShape* shape) :
    export_object(export_object)
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
    export_object->export_material(object.get_material());
}

void GeometricObjectGLSL::export_transformation() {
    export_object->export_transformation(object.get_transformation());
}



void GeometricObjectGLSL::change_export(ExportObject* _export_object) {
    this->export_object = _export_object;
}

void GeometricObjectGLSL::draw() {
    vao.Bind();
    glDrawElements(GL_TRIANGLES, object.get_indices().size(), GL_UNSIGNED_INT, 0);
       
}

