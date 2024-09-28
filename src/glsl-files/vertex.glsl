#version 460 
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 normal;

out vec3 color; 
uniform mat4 transformation;
uniform mat4 cameraProj;

void main () {
    gl_Position =     cameraProj  * transformation  * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = vec3(normal.x, normal.y, normal.z );
}


