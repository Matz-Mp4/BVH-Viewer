#include <algorithm>
#include <cwchar>
#include "../../include/bvh/MCBVH.hpp"
#include <stack>

MCBVH::MCBVH() {
    nodes = new MCBVHNode[10000000]; 
    root_index = -1;
    nodes_size = 0;
    leaves_size = 0;

}

MCBVH::MCBVH(uint num_triangles) {
    uint max_nodes = num_triangles * 2 - 1;
    nodes = new MCBVHNode[max_nodes];  
    root_index = -1;
    nodes_size = 0;
    leaves_size = 0;
}


MCBVH::~MCBVH() {
    delete_nodes();
}


/*
void  sorta_centroids(std::vector<Vector4>& centroids, int axis, int left, int right)  {
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
void sorta_centroids(std::vector<Vector4>& centroids, int axis, int left, int right) {
    int middle = left + (right - left) / 2;

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




void MCBVH::delete_nodes() {
    delete[] nodes;
    nodes_size = 0;
    leaves_size = 0;
}

void MCBVH::init_node(int index) {
    nodes[index].triangle_index = -1;
    nodes[index].bounds = AABB();
    nodes[index].left_index = -1;
    nodes[index].right_index = -1;
}

void MCBVH::build(const Mesh& mesh) {
    std::vector<Vector4> centroids = mesh.centroids();
    root_index = build_node(mesh, 0, 0, (int)centroids.size() - 1, centroids);
}

void MCBVH::tranverse() {}

Mesh MCBVH::into_mesh(unsigned int height) {
    Mesh mesh;
    nodes_into_mesh(root_index, mesh, height);
    return mesh;
}

int MCBVH::build_node(const Mesh& mesh, int axis, int left, int right, std::vector<Vector4>& centroids) {
    int count = right - left + 1;

    if (count == 1) {
        int index = nodes_size++;
        init_node(index);

        int i = (int)centroids[left].w;
        AABB node_bounds = AABB(mesh.vertices[mesh.indices[i * 3 + 0]].position,
                                mesh.vertices[mesh.indices[i * 3 + 1]].position,
                                mesh.vertices[mesh.indices[i * 3 + 2]].position);
        nodes[index].bounds = node_bounds;
        nodes[index].triangle_index = i;

        leaves_size++;
        return index;
    } else {
        sorta_centroids(centroids, axis, left, right);
        int next_axis = (axis + 1) % 3;
        int middle = left + count / 2;

        int node_index = nodes_size++;
        init_node(node_index);

        int left_index = build_node(mesh, next_axis, left, middle - 1, centroids);
        nodes[node_index].left_index = left_index;

        int right_index = build_node(mesh, next_axis, middle, right, centroids);
        nodes[node_index].right_index = right_index;

        nodes[node_index].bounds = AABB(nodes[left_index].bounds, nodes[right_index].bounds);
        return node_index;
    }
}

void MCBVH::nodes_into_mesh(int node_index, Mesh& mesh, unsigned int height) {
    if (node_index == -1) 
        return;

    std::stack<std::pair<int, unsigned int>> stack; 
    stack.push({node_index, 0});  // Coloca o nó inicial e a altura inicial na pilha

    while (!stack.empty()) {
        auto [current_node_index, current_height] = stack.top();
        stack.pop();

        if (current_height <= height) {
            if (current_height == height || (nodes[current_node_index].left_index == -1 && nodes[current_node_index].right_index == -1)) {
                Mesh leaf_mesh = nodes[current_node_index].bounds.generate_mesh();

                for (const Vertex& vertex : leaf_mesh.vertices) {
                    mesh.add_vertex(vertex.position, vertex.normal);
                }

                unsigned int current_vertex_count = mesh.vertices.size();
                for (unsigned int indice : leaf_mesh.indices) {
                    mesh.add_indice(current_vertex_count + indice);
                }
            }

            current_height++;

            if (nodes[current_node_index].left_index != -1) {
                stack.push({nodes[current_node_index].left_index, current_height});
            }

            if (nodes[current_node_index].right_index != -1) {
                stack.push({nodes[current_node_index].right_index, current_height});
            }
        }
    }
}

