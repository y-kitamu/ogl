#version 330 core

layout(location = 0) in vec3 vertexPositioin_modelspace;

void main() {
    gl_Position.xyz = vertexPositioin_modelspace;
    gl_Position.w = 1.0;
}
