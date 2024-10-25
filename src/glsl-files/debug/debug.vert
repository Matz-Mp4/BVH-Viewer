#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 p_matrix;


out vec4 vertex_color; 

void main () {
    gl_Position = p_matrix * v_matrix * m_matrix * position;
    vertex_color = abs(normal);
}
