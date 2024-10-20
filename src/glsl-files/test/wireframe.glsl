#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform mat4 p_matrix; 

const float THICKNESS = 0.003;  

vec3 computeOffset(vec3 edge, vec3 normal) {
    return normalize(cross(edge, normal)) * THICKNESS;
}

out vec4 vertex_color;

void GenerateThickEdge(int index1, int index2, vec3 normal) {
    // Compute the direction of the edge
    vec3 edgeDir = vec3(gl_in[index2].gl_Position - gl_in[index1].gl_Position);

    // Offset direction perpendicular to the edge and the normal
    vec3 offset = computeOffset(edgeDir, normal);

    // Create a quad for the thick edge
    gl_Position = p_matrix * (gl_in[index1].gl_Position + vec4(offset, 0.0));
    vertex_color = vec4(0);
    EmitVertex();
    
    gl_Position = p_matrix * (gl_in[index2].gl_Position + vec4(offset, 0.0));
    vertex_color = vec4(0);
    EmitVertex();
    
    gl_Position = p_matrix * (gl_in[index1].gl_Position - vec4(offset, 0.0));
    vertex_color = vec4(0);
    EmitVertex();
    
    gl_Position = p_matrix * (gl_in[index2].gl_Position - vec4(offset, 0.0));
    vertex_color = vec4(0);
    EmitVertex();
    
    EndPrimitive();
}

void main() {
    vec3 normal = normalize(cross(
        vec3(gl_in[1].gl_Position - gl_in[0].gl_Position),
        vec3(gl_in[2].gl_Position - gl_in[0].gl_Position)
    ));

    GenerateThickEdge(0, 1, normal);  
    GenerateThickEdge(1, 2, normal);  
    GenerateThickEdge(2, 0, normal);  
}

