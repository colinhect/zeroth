#version 440

uniform sampler2D particleTexture;

in vec2 vertexTextureCoords;
in vec3 vertexFinalColor;

out vec4 outputColor;

void main()
{
    outputColor = texture(particleTexture, vertexTextureCoords) * vec4(vertexFinalColor, 1.0) * 0.25;
}