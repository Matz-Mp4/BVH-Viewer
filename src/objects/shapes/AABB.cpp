#include "../../../include/objects/shapes/AABB.hpp"

AABB::AABB():
    bmin(Vector4(0.0, 0.0, 0.0, 1.0)),
    bmax(Vector4(0.0, 0.0, 0.0, 1.0))
{}

AABB::AABB(const Vector4& bmin, const Vector4& bmax) :
    bmin(bmin),
    bmax(bmax)
{}

AABB::AABB( Vector4 p0, Vector4 p1, Vector4 p2) {
    bmin.x = std::min(std::min(p0.x, p1.x), p2.x);
    bmin.y = std::min(std::min(p0.y, p1.y), p2.y);
    bmin.z = std::min(std::min(p0.z, p1.z), p2.z);
    bmin.w = 1.0;

    bmax.x = std::max(std::max(p0.x, p1.x), p2.x);
    bmax.y = std::max(std::max(p0.y, p1.y), p2.y);
    bmax.z = std::max(std::max(p0.z, p1.z), p2.z);
    bmax.w = 1.0;
}

AABB::AABB(AABB& bb0, AABB& bb1) {
    bmin.x = std::min(bb0.bmin.x,bb1.bmin.x);
    bmin.y = std::min(bb0.bmin.y,bb1.bmin.y);
    bmin.z = std::min(bb0.bmin.z,bb1.bmin.z);
    bmin.w = 1.0;


    bmax.x = std::max(bb0.bmax.x,bb1.bmax.x);
    bmax.y = std::max(bb0.bmax.y,bb1.bmax.y);
    bmax.z = std::max(bb0.bmax.z,bb1.bmax.z);
    bmax.w = 1.0;

}

Mesh AABB::generate_mesh() const {
    Mesh mesh;
    std::vector<unsigned int> indices;

    Vector4 p0 = bmin;                          // Bottom-left-front
    Vector4 p1 = Vector4(bmax.x, bmin.y, bmin.z, 1.0);  // Bottom-right-front
    Vector4 p2 = Vector4(bmin.x, bmax.y, bmin.z, 1.0);  // Top-left-front
    Vector4 p3 = Vector4(bmax.x, bmax.y, bmin.z, 1.0);  // Top-right-front

    Vector4 p4 = Vector4(bmin.x, bmin.y, bmax.z, 1.0);  // Bottom-left-back
    Vector4 p5 = Vector4(bmax.x, bmin.y, bmax.z, 1.0);  // Bottom-right-back
    Vector4 p6 = Vector4(bmin.x, bmax.y, bmax.z, 1.0);  // Top-left-back
    Vector4 p7 = bmax;                                 // Top-right-back

    unsigned int idx0 = mesh.add_vertex(p0, Vector4(0, 0, -1, 0));
    unsigned int idx1 = mesh.add_vertex(p1, Vector4(0, -1, 0, 0));
    unsigned int idx2 = mesh.add_vertex(p2, Vector4(-1, 0, 0, 0));
    unsigned int idx3 = mesh.add_vertex(p3, Vector4(-1, -1, -1, 0));
    
    unsigned int idx4 = mesh.add_vertex(p4, Vector4(0, 0, 1, 0));
    unsigned int idx5 = mesh.add_vertex(p5, Vector4(0, 1, 0, 0));
    unsigned int idx6 = mesh.add_vertex(p6, Vector4(1, 0, 1, 0));
    unsigned int idx7 = mesh.add_vertex(p7, Vector4(1, 1, 1, 0));

    indices.push_back(idx0); indices.push_back(idx1); indices.push_back(idx2);
    indices.push_back(idx2); indices.push_back(idx1); indices.push_back(idx3);

    indices.push_back(idx4); indices.push_back(idx6); indices.push_back(idx5);
    indices.push_back(idx5); indices.push_back(idx6); indices.push_back(idx7);

    indices.push_back(idx0); indices.push_back(idx4); indices.push_back(idx2);
    indices.push_back(idx2); indices.push_back(idx4); indices.push_back(idx6);

    indices.push_back(idx1); indices.push_back(idx3); indices.push_back(idx5);
    indices.push_back(idx5); indices.push_back(idx3); indices.push_back(idx7);

    indices.push_back(idx0); indices.push_back(idx4); indices.push_back(idx1);
    indices.push_back(idx1); indices.push_back(idx4); indices.push_back(idx5);

    indices.push_back(idx2); indices.push_back(idx3); indices.push_back(idx6);
    indices.push_back(idx6); indices.push_back(idx3); indices.push_back(idx7);

    mesh.indices = indices;
    return mesh;
}

float AABB::surface_area() const {
    Vector4 e = bmax - bmin; // box extent
    return 2 * (e.x * e.y + e.y * e.z + e.z * e.x); 
}

bool AABB::contains(const AABB& other) const {
    return (bmin.x <= other.bmin.x && bmin.y <= other.bmin.y && bmin.z <= other.bmin.z) &&
           (bmax.x >= other.bmax.x && bmax.y >= other.bmax.y && bmax.z >= other.bmax.z);
}

Vector4 AABB::center() const {
    Vector4 res = (bmin + bmax) * 0.5f;
    res.w = 1.0;
    return res;
}

bool AABB::contains(const Vector4& point) const {
    return (bmin.x <= point.x && bmin.y <= point.y && bmin.z <= point.z) &&
           (bmax.x >= point.x && bmax.y >= point.y && bmax.z >= point.z);
}
void AABB::expand(const Vector4& point) {
    bmin.x = std::min(bmin.x, point.x);
    bmin.y = std::min(bmin.y, point.y);
    bmin.z = std::min(bmin.z, point.z);

    bmax.x = std::max(bmax.x, point.x);
    bmax.y = std::max(bmax.y, point.y);
    bmax.z = std::max(bmax.z, point.z);
}

// Overloaded expand method to expand based on another AABB
void AABB::expand(const AABB& box) {
    expand(box.bmin);
    expand(box.bmax);
}
