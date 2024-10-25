#version 420 

out vec4 FragColor;
in vec4 varying_color;

void main () {
    FragColor = varying_color;
}
