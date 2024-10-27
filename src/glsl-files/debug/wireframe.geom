#version 330 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

uniform mat4 p_matrix;
float thickness = 0.01;  

out vec4 vertex_color;

// Compute the perpendicular offset for thickening edges
vec3 computeOffset(vec3 edge, vec3 normal) {
    return normalize(cross(edge, normal)) * thickness;
}

// Generate a thickened edge between two vertices
void GenerateThickEdge(int index1, int index2, vec3 normal) {
    vec3 edgeDir = vec3(gl_in[index2].gl_Position - gl_in[index1].gl_Position);
    vec3 offset = computeOffset(edgeDir, normal);

    // Define quad vertices to form a thick edge
    vec4 pos1_out = gl_in[index1].gl_Position + vec4(offset, 0.0);
    vec4 pos2_out = gl_in[index2].gl_Position + vec4(offset, 0.0);
    vec4 pos1_in = gl_in[index1].gl_Position - vec4(offset, 0.0);
    vec4 pos2_in = gl_in[index2].gl_Position - vec4(offset, 0.0);

    gl_Position = p_matrix * pos1_out;
    vertex_color = vec4(0.0, 0.0, 0.0, 1.0); // Black outline
    EmitVertex();

    gl_Position = p_matrix * pos2_out;
    vertex_color = vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();

    gl_Position = p_matrix * pos1_in;
    vertex_color = vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();

    gl_Position = p_matrix * pos2_in;
    vertex_color = vec4(0.0, 0.0, 0.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

void main() {
    // Calculate the normal for the triangle
    vec3 normal = normalize(cross(
        vec3(gl_in[1].gl_Position - gl_in[0].gl_Position),
        vec3(gl_in[2].gl_Position - gl_in[0].gl_Position)
    ));

    // Generate thick edges for each edge of the triangle
    GenerateThickEdge(0, 1, normal);
    GenerateThickEdge(1, 2, normal);
    GenerateThickEdge(2, 0, normal);
}

