#include <GL/glew.h>
#include <vector>
#include "../../objects/Vertex.hpp"
#pragma once

class VBO {
    public:
        
        VBO(GLfloat *vertices, GLsizeiptr size);
        VBO(std::vector<Vertex> vertices);
        VBO() = default;

        void   Bind();
        void Unbind();
        void Delete();

        void access_subData(GLfloat *vertices, GLsizeiptr size);

        GLuint ID;
};
