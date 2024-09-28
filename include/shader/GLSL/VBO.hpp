#include <GL/glew.h>
#pragma once

class VBO {
    public:
        
        // Constructor that generates a Vertex Buffer Object and links it to vertices
        VBO(GLfloat *vertices, GLsizeiptr size);
        VBO() = default;

        void   Bind();
        void Unbind();
        void Delete();

        void access_subData(GLfloat *vertices, GLsizeiptr size);

        // Reference ID of the Vertex Buffer Object
        GLuint ID;
};
