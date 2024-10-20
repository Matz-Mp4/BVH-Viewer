#version 330

out vec4 FragColor;

in vec4 vertex_color;
void main () {
    FragColor = vertex_color;
}
