#version 440

uniform float seed;

in vec2 vertexTextureCoords;

out vec4 outputColor;

void main()
{
    vec3 point = vec3(vertexTextureCoords.xy - vec2(0.5), seed);
    float value = 1.0;
    value *= 1.0 - clamp(length(point.xy) * 2.0, 0.0, 1.0);
    value = clamp(value, 0.0, 1.0);
    outputColor = vec4(vec3(value), 1.0);
}
