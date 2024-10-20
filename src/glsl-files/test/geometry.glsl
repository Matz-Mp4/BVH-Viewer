/*#version 330

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
    vec3 color;
} gs_in[];

out vec4 vertex_color;

const float MAGNITUDE = 0.3;
uniform mat4 p_matrix;

void GenerateLine(int index){
    gl_Position = p_matrix * gl_in[index].gl_Position;
    vertex_color = vec4(gs_in[index].color.z, gs_in[index].color.y, gs_in[index].color.x, 1.0);
    EmitVertex();

    gl_Position = p_matrix * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE);
    vertex_color = vec4(gs_in[index].color.z, gs_in[index].color.x, gs_in[index].color.y, 1.0);
    EmitVertex();

    EndPrimitive();
}
void main(){
    GenerateLine(0); 
    GenerateLine(1); 
    GenerateLine(2); 
}
*/

#version 330

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;  // Change to triangle_strip for thick arrow

in VS_OUT {
    vec3 normal;
    vec3 color;
} gs_in[];

out vec4 vertex_color;

const float ARROW_THICKNESS = 0.01;  // Thickness of the arrow body
const float ARROW_LENGTH = 0.2;      // Length of the arrow body
uniform mat4 p_matrix;

void GenerateArrow(int index) {
    // Line segment direction (the normal vector)
    vec3 startPos = vec3(gl_in[index].gl_Position);  // Start point (origin)
    vec3 endPos = startPos + normalize(gs_in[index].normal) * ARROW_LENGTH;  // End point (scaled by length)
    vec3 direction = normalize(endPos - startPos);

    // Find a perpendicular vector to the direction of the arrow for offsetting the quad
    vec3 perp = normalize(cross(direction, vec3(0.0, 0.0, 1.0))) * ARROW_THICKNESS;

    // Emit two vertices on either side of the start point
    gl_Position = p_matrix * vec4(startPos + perp, 1.0);  // Offset top vertex
    vertex_color = vec4(gs_in[index].color.z, gs_in[index].color.y, gs_in[index].color.x, 1.0);
    EmitVertex();

    gl_Position = p_matrix * vec4(startPos - perp, 1.0);  // Offset bottom vertex
    vertex_color = vec4(gs_in[index].color.z, gs_in[index].color.x, gs_in[index].color.y, 1.0);
    EmitVertex();

    // Emit two vertices on either side of the end point
    gl_Position = p_matrix * vec4(endPos + perp, 1.0);  // Offset top vertex at end
    vertex_color = vec4(gs_in[index].color.x, gs_in[index].color.z, gs_in[index].color.y, 1.0);
    vertex_color = vec4(gs_in[index].color, 1.0);
    EmitVertex();

    gl_Position = p_matrix * vec4(endPos - perp, 1.0);  // Offset bottom vertex at end
    vertex_color = vec4(gs_in[index].color.y, gs_in[index].color.z, gs_in[index].color.x, 1.0);
    vertex_color = vec4(gs_in[index].color, 1.0);
    EmitVertex();

    EndPrimitive();
}

void main() {
    for (int i = 0; i < 3; ++i) {
        GenerateArrow(i); 
    }
}

