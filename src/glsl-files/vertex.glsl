#version 460 
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color; 
uniform mat4 transformation;
uniform mat4 cameraProj;

void main () {
    gl_Position =   transformation * cameraProj * vec4(aPos, 1.0);
    color = aColor;
}


