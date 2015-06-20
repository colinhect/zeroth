#version 440

uniform float seed;

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence, 
    in  int     octaveCount);

float random(
    in  float   seed,
    in  float   min,
    in  float   max);

const float seeds[2] = float[2](
    random(seed, -10000.0, 10000.0),
    random(seed, -10000.0, 10000.0)
);

void proceduralTexture(
    in  vec2    textureCoords,
    out vec4    outputColor)
{
    vec2 point = textureCoords - 0.5;

    float shape = fractalNoise(vec3(point, seeds[0]) * 6.0, 2.0, 0.5, 8);
    shape = clamp(shape, -1.0, 1.0) * 1.3;
    shape = pow(shape, 3.0);

    float value = fractalNoise(vec3(point, seeds[1]) * 2.0, 2.0, 0.5, 6);
    value = value * 0.5 + 0.5;
    value *= 1.0 - clamp((length(point) + 1.0 + shape * 0.02) * 0.7, 0.0, 1.0);
    value = clamp(value, 0.0, 1.0);

    outputColor = vec4(vec3(value), 1.0);
}
