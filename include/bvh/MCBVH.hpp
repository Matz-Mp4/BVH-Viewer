#pragma once

#include "BVH.hpp"
#include "../objects/shapes/AABB.hpp"
#include <functional>
#include <future>

/*
 * Mid-Cut Bounding Volume Hierarchy 
 */
class MCBVH: BVH {
    public:
        MCBVH();
        MCBVH(uint num_triangles); 
       ~MCBVH();

        void build(const Mesh& mesh) override;
        void tranverse() override;
        Mesh into_mesh(unsigned int height) override;

        uint nodes_size;
        uint leaves_size;

    private:
        struct MCBVHNode {
            int triangle_index = -1;
            AABB bounds;
            int left_index = -1;  
            int right_index = -1;         
        };

        MCBVHNode* nodes;  
        int root_index;    

        void init_node(int index);
        int build_node(const Mesh& mesh, int axis, int left, int right, std::vector<Vector4>& centroids);
        void delete_nodes();
        void    nodes_into_mesh(int node_index, Mesh& mesh, unsigned int height) ;

};
