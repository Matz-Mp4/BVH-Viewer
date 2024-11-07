#include <algorithm>
#include <iostream>
#include "../../include/bvh/MDBVH.hpp"



MDBVH::MDBVH() {
    init_node(&root);
}

MDBVH::~MDBVH() {
    delete_node(root.left);
    delete_node(root.right);
    /* delete_tree(&root); */
}


void  sort_centroids(std::vector<Vector4> centroids, int axis, int left, int right)  {
    std::sort(
        centroids.begin() + left,
        centroids.begin() + right + 1,
        [axis] (const Vector4& a, const Vector4& b) {
             if (axis == 0) 
                 return a.x < b.x;
             else if (axis == 1) 
                  return a.y < b.y;
             else 
                  return a.z < b.z;
        } 
    );

}




void MDBVH::build(const Mesh& mesh) {
    std::vector<Vector4> centroids = mesh.centroids();
    MDBVHNode* root = build_node(mesh, mesh.vertices.size(), 0, 0, (int)centroids.size() - 1, centroids);
    this->root = *root;
    delete root;
}

//TODO
void MDBVH::tranverse() {}
Mesh MDBVH::into_mesh(unsigned int height) {
    Mesh mesh;
    nodes_into_mesh(&root, mesh, 0, height);
    return mesh;
}

void MDBVH::init_node(MDBVHNode* node) {
    node->trinagle_index = -1;
    node->bounds = AABB();
    node->left = nullptr;
    node->right= nullptr;

}

MDBVH::MDBVHNode* MDBVH::build_node(const Mesh& mesh, int n_vertices, int axis, int left, int right, std::vector<Vector4> centroids) {
    int count = right - left + 1;

    if(count   == 1)  {
       MDBVH::MDBVHNode* node = new MDBVH::MDBVHNode;
       init_node(node);
        int i = (int) centroids[left].w;
        AABB node_bounds = AABB(mesh.vertices[i * 3 + 0].position, 
                                mesh.vertices[i * 3 + 1].position,
                                mesh.vertices[i * 3 + 2].position);
        node->bounds = node_bounds;
        node->trinagle_index = i;
        return node;

    //there are two or more triangles 
    } else {
        sort_centroids(centroids, axis, left, right);
        int next_axis = (axis + 1) % 3;
        int middle = left + count / 2;

        MDBVH::MDBVHNode* node = new MDBVH::MDBVHNode;
        MDBVH::MDBVHNode* left_node = new MDBVH::MDBVHNode;
        MDBVH::MDBVHNode* right_node = new MDBVH::MDBVHNode;

        left_node = build_node(mesh, n_vertices, next_axis, left, middle - 1, centroids);
        node->left = left_node;

        right_node = build_node(mesh, n_vertices, next_axis, middle, right, centroids);
        node->right = right_node;

        //build the bvh for this node 
        AABB bv_left = AABB((node->left)->bounds);
        AABB bv_right = AABB((node->right)->bounds);
        node->bounds = AABB(bv_left, bv_right);

        node->trinagle_index = -1;

        return node;

    }
}

void MDBVH::delete_node(MDBVH::MDBVHNode* node) {
    if (node != nullptr) {
        MDBVHNode* left_node = node->left;
        MDBVHNode* right_node= node->right;

        delete node;
        node = nullptr;

        delete_node(left_node);
        delete_node(right_node);

    }
}

void MDBVH::nodes_into_mesh(MDBVH::MDBVHNode* node, Mesh& mesh, unsigned int count, unsigned int height) {
     if (node == nullptr) 
         return;

    if (count <= height) {
        if(count == height) {
            Mesh leaf_mesh = node->bounds.generate_mesh();

            for (const Vertex& vertex : leaf_mesh.vertices) {
                mesh.add_vertex(vertex.position, vertex.normal);
            }
            
            unsigned int current_vertex_count = mesh.vertices.size();
            for (unsigned int indice : leaf_mesh.indices) {
                mesh.add_indice(current_vertex_count + indice);
            }
        }
        nodes_into_mesh(node->left, mesh, count  + 1, height);
        nodes_into_mesh(node->right, mesh, count + 1, height);
    }
}


