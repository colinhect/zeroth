#version 410

uniform sampler2D noiseTexture;

in vec2 vertexTextureCoords;

out vec3 outputColor;

void main()
{
    outputColor = texture(noiseTexture, vertexTextureCoords).rgb;
}
