#include <GL/glew.h>
#pragma once

class EBO{
    public:
        EBO(GLuint* indices, GLsizeiptr size);

        void    Bind();
        void  Unbind();
        void  Delete();
        
        // ID reference for the Vertex Array Indices
        GLuint ID;
};
