#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

out VS_OUT {
    vec3 normal;
    vec3 color;
}vs_out;

uniform mat4 v_matrix;
uniform mat4 m_matrix;

void main () {
    gl_Position = v_matrix * m_matrix * position;
    mat4 n_matrix = mat4(transpose(inverse(v_matrix * m_matrix)));
    vs_out.normal = normalize(vec3(vec4(n_matrix * normal)));
    vs_out.color = abs(vec3(normal));
}
