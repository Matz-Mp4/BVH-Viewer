
#include "../../../include/shader/GLSL/VAO.hpp"

VAO ::VAO(){
    glGenVertexArrays(1, &ID);
}

void VAO ::LinkVBO(VBO &VBO, GLuint layout){
    VBO.Bind();
    glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glEnableVertexAttribArray(layout);
}
void VAO ::Bind(){
    glBindVertexArray(ID);
}

void VAO ::Unbind(){
    glBindVertexArray(0);
}

void VAO ::Delete(){
    glDeleteVertexArrays(1, &ID);
}
