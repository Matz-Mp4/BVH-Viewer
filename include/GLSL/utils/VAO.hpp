#include "VBO.hpp"
#pragma once

class VAO {
    public:
        // ID reference for the Vertex Array Object
        GLuint ID;
        // Constructor that generates a VAO ID
        VAO();

        // Links a VBO to the VAO using a certain layout
        void LinkAttrib(VBO &VBO, GLuint layout, GLuint num_components, GLenum type , GLsizeiptr stride, void* offset);
        void    Bind();
        void  Unbind();
        void  Delete();
};
