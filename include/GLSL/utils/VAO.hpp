#include "VBO.hpp"
#pragma once

class VAO {
    public:
        GLuint ID;
        VAO();

        void LinkAttrib(VBO &VBO, GLuint layout, GLuint num_components, GLenum type , GLsizeiptr stride, void* offset);
        void    Bind();
        void  Unbind();
        void  Delete();
};
