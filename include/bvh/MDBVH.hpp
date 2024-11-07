#pragma once 

#include "BVH.hpp"
#include "../objects/shapes/AABB.hpp"
/*
 * Mid-Cut Bounding Volume Hiearchy
 */
class MDBVH: BVH {
    public:
         MDBVH();
        ~MDBVH();
         void     build(const Mesh& mesh) override;
         void tranverse() override;
         Mesh into_mesh(unsigned int height) override;

    private:

        struct MDBVHNode {
            int trinagle_index = -1;
            AABB bounds;
            MDBVHNode* left;
            MDBVHNode* right;
        };

        MDBVHNode root;

        void        init_node(MDBVHNode*  node);
        MDBVHNode* build_node(const Mesh& mesh, int n_vertices, int axis, int left, int right, std::vector<Vector4> centroids);
        void      delete_node(MDBVHNode* node);
        void  nodes_into_mesh(MDBVH::MDBVHNode* node, Mesh& mesh, unsigned int count, unsigned int height) ;

};
