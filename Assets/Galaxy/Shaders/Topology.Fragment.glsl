#version 440

uniform sampler2D topologyTexture;
uniform float brightness;

in vec3 vertexPosition;
in vec2 vertexTextureCoords;

bool renderStage(
    out vec4    outColor)
{
    float falloff = clamp((length(vertexPosition) - 10000.0) * 0.00001, 0.0, 1.0);
    outColor = texture(topologyTexture, vertexTextureCoords) * brightness * falloff;
    return true;
}