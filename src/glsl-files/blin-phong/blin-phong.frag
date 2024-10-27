#version 330 

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

uniform mat4            v_matrix;

in vec3      varying_normal;
in vec3   varying_light_dir;
in vec3    varying_vert_pos;
in vec3 varying_half_vector;
out vec4 FragColor;

void main () {
    vec3 L = normalize(varying_light_dir);
    vec3 N = normalize(varying_normal);
    vec3 V = normalize(-v_matrix[3].xyz - varying_vert_pos);
    vec3 H = normalize(varying_half_vector);

    //Angle between the light and surface normal
    float cos_theta = dot(L, N);

    //Angle between the view vector and reflected light 
    float cos_phi = dot(H, N);

    //Ambient, Directional and Specular contributions
    vec3 effective_color = (amb_light.color.xyz * material.color.xyz) + (point_light.color.xyz * material.color.xyz);

    vec3 ambient = effective_color * material.k_amb;
    vec3 diffuse = effective_color * material.k_dif * max(cos_theta, 0.0);
    //The 3.0 at in the end is a "tweak" to imrpove the specular highlight
    vec3 specular = point_light.color.xyz * material.k_spec * pow(max(cos_phi, 0.0f), material.exp * 3.0);

    FragColor = vec4((ambient + diffuse + specular), 1.0);
}
