#version 420

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

out vec3 color; 

struct PointLight{
    vec4 color;
    vec4 position;
};

struct AmbientLight{
    vec4 color;
};

struct Material {
	vec3   color;
    float  k_amb;
    float  k_dif;
    float  k_spec;
    float  exp;
};

uniform Material        material;

uniform AmbientLight   amb_light;
uniform PointLight   point_light;

uniform mat4            m_matrix;
uniform mat4            v_matrix;
uniform mat4            p_matrix;
uniform mat4         norm_matrix;

void main () {
    gl_Position = p_matrix * v_matrix * m_matrix * position;

    /* vec4 diffuse = (0.0); */
    /* vec4 specular = (0.0); */

    color = vec3(normal.x, normal.y, normal.z);
}
