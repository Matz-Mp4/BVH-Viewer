#include <GL/glew.h>
#include <vector>
#pragma once

class EBO{
    public:
        EBO() = default;
        EBO(GLuint* indices, GLsizeiptr size);
        EBO(std::vector<unsigned int> indices);

        void    Bind();
        void  Unbind();
        void  Delete();
        
        GLuint ID;
};
