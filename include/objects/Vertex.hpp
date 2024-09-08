#pragma once

#include "../math/Vector3.hpp"

class Vertex {
    public:
        Vector3 position;
        Vector3 normal;

        Vertex() = default;
        ~Vertex() = default;

        Vertex(Vector3 position, Vector3 normal);
};
