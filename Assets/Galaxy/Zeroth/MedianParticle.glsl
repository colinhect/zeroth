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

    float shape = fractalNoise((point + seed + 123.0) * 4.0, 2.0, 0.5, 4);
    float detail = fractalNoise(point * 2.0, 2.0, 0.5, 6) * 0.5 + 0.5;

    float value = detail;
    value *= 1.0 - clamp((length(point.xy + shape * 0.1) + 1.0) * 0.7, 0.0, 1.0);
    value = clamp(value, 0.0, value);
    outputColor = vec4(vec3(0.62, 0.71, 0.86) * value, 1.0);
}
