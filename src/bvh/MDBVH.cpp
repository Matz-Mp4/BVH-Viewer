#include <algorithm>
#include <cwchar>
#include <iostream>
#include "../../include/bvh/MDBVH.hpp"
#include <limits>
#include <stack>



MDBVH::MDBVH() {
    init_node(&root);
}

MDBVH::~MDBVH() {
    delete_node(root.left);
    delete_node(root.right);
    /* delete_tree(&root); */
}

void sort_centroids(std::vector<Vector4>& centroids, int axis, int left, int right) {
    int middle = left + (right - left) / 2;

    // Perform median of three heuristic for better pivot selection
    int a = left, b = middle, c = right;
    if ((axis == 0 && centroids[a].x > centroids[b].x) || (axis == 1 && centroids[a].y > centroids[b].y) || (axis == 2 && centroids[a].z > centroids[b].z)) {
        std::swap(a, b);
    }
    if ((axis == 0 && centroids[b].x > centroids[c].x) || (axis == 1 && centroids[b].y > centroids[c].y) || (axis == 2 && centroids[b].z > centroids[c].z)) {
        std::swap(b, c);
    }
    if ((axis == 0 && centroids[a].x > centroids[b].x) || (axis == 1 && centroids[a].y > centroids[b].y) || (axis == 2 && centroids[a].z > centroids[b].z)) {
        std::swap(a, b);
    }

    // Use nth_element to find the median
    std::nth_element(
        centroids.begin() + left,
        centroids.begin() + middle,
        centroids.begin() + right + 1,
        [axis](const Vector4& a, const Vector4& b) {
            if (axis == 0) return a.x < b.x;
            else if (axis == 1) return a.y < b.y;
            else return a.z < b.z;
        }
    );
}


/*
void  sort_centroids(std::vector<Vector4>& centroids, int axis, int left, int right)  {
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

}*/

void MDBVH::build(const Mesh& mesh) {
    std::vector<Vector4> centroids = mesh.centroids();
    MDBVHNode* root = build_node(mesh, 0, 0, (int)centroids.size() - 1, centroids);
    this->root = *root;
    delete root;
}

//TODO
void MDBVH::tranverse() {}
Mesh MDBVH::into_mesh(unsigned int height) {
    Mesh mesh;
    nodes_into_mesh(&root, mesh,  0,height);
    return mesh;
}

void MDBVH::init_node(MDBVHNode* node) {
    node->trinagle_index = -1;
    node->bounds = AABB();
    node->left = nullptr;
    node->right= nullptr;

}

/*
MDBVH::MDBVHNode* MDBVH::build_node(const Mesh& mesh,  int depth, int left, int right, std::vector<Vector4>& centroids) {
    int count = right - left + 1;

    // Base case: if count is 1, create a leaf node
    if (count <= 1) {
        MDBVHNode* node = new MDBVHNode();
        init_node(node);

        int i = static_cast<int>(centroids[left].w);  // Access the actual triangle index
        node->bounds = AABB(
            mesh.vertices[mesh.indices[i * 3]].position,
            mesh.vertices[mesh.indices[i * 3 + 1]].position,
            mesh.vertices[mesh.indices[i * 3 + 2]].position
        );
        node->trinagle_index = i;
        return node;
    }

    // Find the best axis and split using SAH
    int best_axis = -1;
    int best_split = -1;
    float best_cost = std::numeric_limits<float>::infinity();

    // Check each axis for the best split
    for (int axis = 0; axis < 3; ++axis) {
        sort_centroids(centroids, axis, left, right);

        // Initialize cumulative bounding boxes for the left and right sets
        std::vector<AABB> left_bounds_array(count), right_bounds_array(count);

        // Compute left bounds
        left_bounds_array[0] = AABB(mesh.vertices[mesh.indices[left * 3]].position,
                                     mesh.vertices[mesh.indices[left * 3 + 1]].position,
                                     mesh.vertices[mesh.indices[left * 3 + 2]].position);
        for (int i = left + 1; i <= right; ++i) {
            AABB temp = AABB(mesh.vertices[mesh.indices[i * 3]].position,
                                                    mesh.vertices[mesh.indices[i * 3 + 1]].position,
                                                    mesh.vertices[mesh.indices[i * 3 + 2]].position);
            left_bounds_array[i - left] = AABB(left_bounds_array[i - left - 1], temp);
        }

        // Compute right bounds
        right_bounds_array[right - left] = AABB(mesh.vertices[mesh.indices[right * 3]].position,
                                                 mesh.vertices[mesh.indices[right * 3 + 1]].position,
                                                 mesh.vertices[mesh.indices[right * 3 + 2]].position);
        for (int i = right - 1; i >= left; --i) {
        AABB temp = AABB(mesh.vertices[mesh.indices[i * 3]].position,
                                                    mesh.vertices[mesh.indices[i * 3 + 1]].position,
                                                    mesh.vertices[mesh.indices[i * 3 + 2]].position);
         
            right_bounds_array[i - left] = AABB(right_bounds_array[i - left + 1], temp);
        }

        // Evaluate split costs
        for (int i = left; i < right; ++i) {
            float left_area = left_bounds_array[i - left].surface_area();
            float right_area = right_bounds_array[i - left + 1].surface_area();

            int left_count = i - left + 1;
            int right_count = right - i;

            float cost = (left_area * left_count + right_area * right_count);

            if (cost < best_cost) {
                best_cost = cost;
                best_axis = axis;
                best_split = i;
            }
        }
    }

    // Sort centroids along the best axis and split at the best split point
    sort_centroids(centroids, best_axis, left, right);
    int middle = best_split + 1;

    MDBVHNode* node = new MDBVHNode();
    node->left = build_node(mesh, depth + 1, left, middle - 1, centroids);
    node->right = build_node(mesh,  depth + 1, middle, right, centroids);

    // Merge bounding boxes for left and right children
    node->bounds = AABB(node->left->bounds, node->right->bounds);

    node->trinagle_index = -1;  // Non-leaf nodes do not directly hold triangle indices

    return node;
}*/


MDBVH::MDBVHNode* MDBVH::build_node(const Mesh& mesh, int axis, int left, int right, std::vector<Vector4>& centroids) {
    int count = right - left + 1;

    if(count   == 1)  {
       MDBVH::MDBVHNode* node = new MDBVH::MDBVHNode();
       init_node(node);
        int i = (int) centroids[left].w;
        int j = i ;
        AABB node_bounds = AABB(mesh.vertices[mesh.indices[j * 3 + 0]].position, 
                                mesh.vertices[mesh.indices[j * 3 + 1]].position,
                                mesh.vertices[mesh.indices[j * 3 + 2]].position);
        node->bounds = node_bounds;
        node->left = nullptr;
        node->right= nullptr;
        node->trinagle_index = i;
        return node;

    } else {
        sort_centroids(centroids, axis, left, right);
        int next_axis = (axis + 1 ) % 3;
        int middle = left + count / 2;

        MDBVH::MDBVHNode* node = new MDBVH::MDBVHNode();
        MDBVH::MDBVHNode* left_node = new MDBVH::MDBVHNode();
        MDBVH::MDBVHNode* right_node = new MDBVH::MDBVHNode();
        
        AABB temp = AABB();
        left_node = build_node(mesh,  next_axis, left, middle - 1 , centroids);
        node->left = left_node;

        right_node = build_node(mesh,  next_axis, middle, right, centroids);
        node->right = right_node;

        //build the bvh for this node 
        AABB bv_left = AABB(temp,(node->left)->bounds);
        AABB bv_right = AABB(temp,(node->right)->bounds);
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
        if(count == height || (node->left == nullptr && node->right == nullptr)) {
            Mesh leaf_mesh = node->bounds.generate_mesh();

            for (const Vertex& vertex : leaf_mesh.vertices) {
                mesh.add_vertex(vertex.position, vertex.normal);
            }
            
            unsigned int current_vertex_count = mesh.vertices.size();
            for (unsigned int indice : leaf_mesh.indices) {
                mesh.add_indice(current_vertex_count + indice);
            }
        }
        count++;
        nodes_into_mesh(node->left, mesh, count , height);
        nodes_into_mesh(node->right, mesh, count , height);
     } 
}

