#version 440

layout(location = 0) in vec3 position;
layout(location = 1) in int layer;

out int vertexLayer;

void main()
{
    gl_Position = vec4(position, 1.0);
    vertexLayer = layer;
}
