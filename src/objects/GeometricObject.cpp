#include "../../include/objects/GeometricObject.hpp"

GeometricObject::GeometricObject(const IShape* shape, const Material& _material) {
    material = _material;
    mesh = shape->generate_mesh();
}


GeometricObject::GeometricObject(const Mesh& _mesh, const Material& _material) {
    material = _material;
    mesh = _mesh;
}

GeometricObject  GeometricObject::with_material(const Material& _material) {
    return GeometricObject(mesh, _material);
}


GeometricObject  GeometricObject::with_shape(const IShape* shape) {
    return GeometricObject(shape, material);
}
