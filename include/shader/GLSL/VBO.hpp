#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class VBO {
    public:
        // Reference ID of the Vertex Buffer Object
        GLuint ID;
        // Constructor that generates a Vertex Buffer Object and links it to vertices
        VBO(GLfloat *vertices, GLsizeiptr size);

        void   Bind();
        void Unbind();
        void Delete();

        void access_subData(GLfloat *vertices, GLsizeiptr size);
};
