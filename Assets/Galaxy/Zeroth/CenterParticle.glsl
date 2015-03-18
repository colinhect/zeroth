#version 440

uniform float seed;
uniform vec4 color;

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence, 
    in  int     octaveCount);

void proceduralTexture(
    in  vec2    textureCoords,
    out vec4    outputColor)
{
    vec3 point = vec3(textureCoords - 0.5, seed);

    float shape = clamp(fractalNoise((point + seed + 53.0) * 2.0, 2.0, 0.5, 4), -1.0, 1.0) * 1.1;
    shape = pow(shape, 2.0);

    float value = fractalNoise(point * 2.0, 2.0, 0.5, 4) * 0.5 + 0.5;
    value *= 1.0 - clamp((length(point.xy + shape * 0.1) + 1.0) * 0.7, 0.0, 1.0);
    value = clamp(value, 0.0, 1.0);

    outputColor = color * value;
}
