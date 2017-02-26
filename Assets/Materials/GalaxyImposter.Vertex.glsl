#version 440

uniform mat4 modelViewProjection;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in float vertexSize;

out vec3 galaxyColor;

void main()
{
    gl_Position = modelViewProjection * vec4(vertexPosition, 1.0);
    gl_PointSize = vertexSize;

    galaxyColor = vertexColor;
}
