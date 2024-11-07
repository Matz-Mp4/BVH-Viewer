#pragma once
#include "../objects/Mesh.hpp"

/*
 * Bounding Volume Hiearchy
 */
class BVH {
    public: 
        virtual     void build(const Mesh& mesh) = 0;
        virtual void tranverse() = 0;
        virtual Mesh into_mesh(unsigned int height) = 0;
};
