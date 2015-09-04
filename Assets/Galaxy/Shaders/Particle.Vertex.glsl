#version 440

uniform mat4 model;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in float size;
layout(location = 3) in float rotation;

out vec3 vertexColor;
out float vertexSize;
out float vertexRotation;

void main()
{
    gl_Position = model * vec4(position, 1.0);
    vertexColor = color;
    vertexSize = size;
    vertexRotation = rotation;
}