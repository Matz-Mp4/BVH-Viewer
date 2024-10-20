#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

out vec3 color; 
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 p_matrix;

void main () {
    gl_Position = p_matrix * v_matrix * m_matrix * position;
    color = abs(vec3(normal));
}
