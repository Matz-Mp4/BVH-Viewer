#version 420

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;


struct PointLight{
    vec4 color;
    vec4 position;
};

struct AmbientLight{
    vec4 color;
};

struct Material {
	vec4   color;
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

out vec4 varying_color;

void main () {
    vec4 P = m_matrixq * position;
    vec3 N = normalize(norm_matrix * vec4(normal, 1.0).xyz);
    vec3 L = normalize(point_light.position - P.xyz);
    vec3 V = normalize(-v_matrix[3].xyz - P.xyz);
    vec3 R = reflect(-L, N);

    vec3 effective_color = ((ambient.color * material.color) + (point_light.color * material)).xyz;

    vec3 ambient = effective_color * material.k_amb;
    vec3 diffuse = effective_color * material.k_dif * max(dot(N,L), 0.0);
    vec3 specular = point_light.color * material.specular * pow(max(dot(R,V), 0.0f), material.exp);

    varying_color = vec4((ambient + diffuse + specular), 1.0);
    gl_Position = p_matrix * v_matrix * m_matrix * position;

}
