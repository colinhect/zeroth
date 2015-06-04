#version 440

uniform sampler2D particleTexture;

in vec2 vertexTextureCoords;
in float vertexFinalBrightness;

out vec4 outputColor;

void main()
{
    outputColor = texture(particleTexture, vertexTextureCoords) * vertexFinalBrightness;
}