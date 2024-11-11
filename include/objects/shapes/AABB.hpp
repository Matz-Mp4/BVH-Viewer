#pragma once

#include "../IShape.hpp"
#include "../../math/Vector4.hpp"

/*
 * Axes-Aligned Bounding Box
 */
class AABB : public IShape {
    public:

         AABB(const Vector4& bmin, const Vector4& bmax);
         //From a triangle
         AABB(Vector4 p0, Vector4 p1, Vector4 p2);
         //From a union of AABBs
         AABB(AABB& bb0, AABB& bb1);
         AABB();
        ~AABB() = default;

         Mesh  generate_mesh() const override;
         AABB with_boundings(const Vector4& bmin, const Vector4& bmax);
         float  surface_area() const;
         bool contains(const AABB& other) const;
         bool contains(const Vector4& point) const;
         Vector4 center() const;
         void expand(const Vector4& point) ;
        void expand(const AABB& box) ;


        Vector4 bmin;
        Vector4 bmax;

};
 
