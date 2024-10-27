#version 330

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

struct PointLight {
    vec4 color;
    vec4 position;
};

uniform PointLight point_light;

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 p_matrix;

out vec3 varying_normal;
out vec3 varying_light_dir;
out vec3 varying_vert_pos;
out vec3 varying_half_vector;

void main() {
    mat4 norm_matrix = transpose(inverse(m_matrix));

    varying_vert_pos = (m_matrix * position).xyz;
    varying_light_dir = point_light.position.xyz - varying_vert_pos;
    varying_normal = (norm_matrix * vec4(normal.xyz, 1.0)).xyz;
    varying_half_vector = varying_light_dir - varying_vert_pos;

    gl_Position = p_matrix * v_matrix * m_matrix * position;
}

