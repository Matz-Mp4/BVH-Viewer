#version 420 

struct Material {
	vec3 color;
    float  k_amb;
    float  k_dif;
    float  k_spec;
    float  k_trans;
    float  exp;
    float  index_ref;
};

uniform Material mateiral;

out vec4 FragColor;
in vec3 color;

void main () {
    FragColor = vec4(0.3, 0.5, 1.0, 1.0f);
}
