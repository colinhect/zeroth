#version 410

uniform sampler2D densityMap;

in vec2 vertexTextureCoords;

out vec3 outputColor;

void main()
{
    outputColor = texture(densityMap, vertexTextureCoords).rgb;
}
