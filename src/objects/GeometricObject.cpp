#include "../../include/objects/GeometricObject.hpp"
#include "../../include/math/Transforamation.hpp"
#include <glm/trigonometric.hpp>

GeometricObject::GeometricObject(const IShape* shape, const Material& _material) {
    material = _material;
    mesh = shape->generate_mesh();
    transformation =  UNIT_MATRIX4;
}

GeometricObject::GeometricObject(const IShape* shape, const Material& _material, const Matrix4& _transformation) {
    material = _material;
    mesh = shape->generate_mesh();
    transformation =  _transformation;
}

GeometricObject::GeometricObject(const Mesh& _mesh, const Material& _material, const Matrix4& _transformation) {
    material = _material;
    mesh = _mesh;
    transformation = _transformation;
}

GeometricObject  GeometricObject::with_material(const Material& _material) {
    return GeometricObject(mesh, _material, transformation);
}


GeometricObject  GeometricObject::with_shape(const IShape* shape) {
    return GeometricObject(shape, material, transformation);
}


GeometricObject  GeometricObject::with_transformation(const Matrix4& transformation) {
    return GeometricObject(mesh, material, transformation);
}


void GeometricObject::transform(Matrix4& _transformation) {
    this->transformation =  _transformation *  transformation;
}


Matrix4 GeometricObject::get_transformation() const {
    return transformation;
}

Material GeometricObject::get_material() const {
    return material;
}

Mesh GeometricObject::get_mesh() const {
    return mesh;
}


std::vector<Vertex> GeometricObject::get_vertices() const {
    return mesh.vertices;
}


std::vector<unsigned int> GeometricObject::get_indices() const {
    return mesh.indices;
}
