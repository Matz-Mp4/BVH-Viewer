#pragma once

#include "../math/Vector4.hpp"

class Vertex {
    public:
        Vector4 position;
        Vector4 normal;

        Vertex() = default;
        ~Vertex() = default;

        Vertex(Vector4 position, Vector4 normal);
};
