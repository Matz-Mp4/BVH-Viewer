#version 420

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

out vec3 color; 
uniform mat4 transformation;
uniform mat4 cam_proj;

void main () {
    gl_Position = cam_proj  * transformation  * position;
    color = vec3(normal.x, normal.y, normal.z);
}
