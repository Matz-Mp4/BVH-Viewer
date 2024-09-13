#include "../../../include/shader/GLSL/VBO.hpp"
// Constructor that generates a Vertex Buffer Object and links it to vertices
VBO::VBO(GLfloat *vertices, GLsizeiptr size){
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete(){
    glDeleteBuffers(1, &ID);
}

void VBO::access_subData(GLfloat *vertices, GLsizeiptr size){
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
}
