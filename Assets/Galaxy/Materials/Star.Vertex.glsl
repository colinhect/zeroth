#version 440

uniform vec3 cameraPosition;
uniform mat4 model;
uniform mat4 modelViewProjection;

layout(location = 0) in vec3 position;
layout(location = 1) in float size;
layout(location = 2) in float brightness;
layout(location = 3) in float distance;

out float vertexBrightness;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);
    gl_PointSize = size;
    vertexBrightness = brightness;

    vec3 worldPosition = (model * vec4(position, 1.0)).xyz;
    vertexBrightness *= pow(clamp((1.0 - clamp(length(worldPosition - cameraPosition), 0, distance) / distance), 0.0, 1.0), 2.0);
}