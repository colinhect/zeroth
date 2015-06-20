#version 440

uniform mat4 modelView;
uniform mat4 modelViewProjection;

layout(location = 0) in vec3 position;
layout(location = 3) in vec2 textureCoords;

out vec3 vertexPosition;
out vec2 vertexTextureCoords;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);
    vertexPosition = (modelView * vec4(position, 1.0)).xyz;
    vertexTextureCoords = textureCoords;
}