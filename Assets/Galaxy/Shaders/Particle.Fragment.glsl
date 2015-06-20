#version 440

uniform sampler2D particleTexture;
uniform float brightness;

in vec2 vertexTextureCoords;
in vec3 vertexFinalColor;

out vec4 outputColor;

void main()
{
    float intensity = texture(particleTexture, vertexTextureCoords).r;
    outputColor = vec4(vertexFinalColor, 1.0) * intensity * brightness;
}