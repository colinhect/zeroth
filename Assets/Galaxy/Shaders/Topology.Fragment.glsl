#version 440

uniform sampler2D topologyTexture;
uniform float brightness;

in vec3 vertexPosition;
in vec2 vertexTextureCoords;

bool renderStage(
    out vec4    color)
{
    float falloff = clamp((length(vertexPosition) - 10000.0) * 0.00001, 0.0, 1.0);
    color = texture(topologyTexture, vertexTextureCoords) * brightness * falloff;
    return true;
}