#version 440

uniform float seed;

in vec2 vertexTextureCoords;

out vec4 outputColor;

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence, 
    in  int     octaveCount);

void main()
{
    vec3 point = vec3(vertexTextureCoords.xy - vec2(0.5), seed);
    float value = fractalNoise(point * 5.0, 2.0, 0.5, 2) * 0.2 + 0.8;
    value *= pow(1.0 - clamp(length(point.xy) * 2.0, 0.0, 1.0), 3.0);
    value = clamp(value, 0.0, 1.0);
    outputColor = vec4(vec3(0.62, 0.71, 0.86) * value, 1.0);
}
