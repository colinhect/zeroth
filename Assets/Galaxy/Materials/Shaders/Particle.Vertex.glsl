#version 440

uniform mat4 modelViewProjection;

layout(location = 0) in vec3 position;
layout(location = 1) in float size;
layout(location = 2) in float rotation;
layout(location = 3) in float brightness;

out float vertexSize;
out float vertexRotation;
out float vertexBrightness;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);
    vertexSize = size;
    vertexRotation = rotation;
    vertexBrightness = brightness;
}