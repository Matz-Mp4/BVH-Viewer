#version 330

struct PointLight {
    vec4 color;
    vec4 position;
};

struct AmbientLight {
    vec4 color;
};

struct Material {
    vec4 color;
    float k_amb;
    float k_dif;
    float k_spec;
    float exp;
};

uniform Material material;
uniform AmbientLight amb_light;
uniform PointLight point_light;

in vec3 varying_normal;
in vec3 varying_light_dir;
in vec3 varying_vert_pos;
out vec4 FragColor;

// Function to determine the cel shading level
int getCelShadingLevel(float cosTheta) {
    if (cosTheta > 0.8) return 3; 
    else if (cosTheta > 0.5) return 2; 
    else if (cosTheta > 0.2) return 1; 
    return 0; 
}

void main() {
    vec3 L = normalize(varying_light_dir);
    vec3 N = normalize(varying_normal);
    vec3 V = normalize(-varying_vert_pos); // Corrected to use varying_vert_pos

    float cos_theta = dot(L, N);
    int shadingLevel = getCelShadingLevel(cos_theta);
    
    vec3 color = material.color.xyz * point_light.color.xyz;
    vec3 ambient = amb_light.color.xyz * material.color.xyz * material.k_amb;

    vec3 diffuse;
    if (shadingLevel == 3) {
        diffuse = color * material.k_dif * 1.0; // Bright
    } else if (shadingLevel == 2) {
        diffuse = color * material.k_dif * 0.8; // Bright
    } else if (shadingLevel == 1) {
        diffuse = color * material.k_dif * 0.5; // Mid
    } else {
        diffuse = color * material.k_dif * 0.2; // Dark
    }

    vec3 specular = point_light.color.xyz * material.k_spec * pow(max(dot(normalize(V), N), 0.0), material.exp * 3.0);

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}

