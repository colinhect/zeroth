#version 440

uniform float seed;
uniform float eccentricity;
uniform float armThickness;

const vec3 bulgeColor = vec3(244.0, 216.0, 203.0) / 255.0;
const float bulgeSize = 0.5;

const vec3 primaryColor = vec3(130.0, 157.0, 184.0) / 255.0;

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence, 
    in  int     octaveCount);

float galaxyBar(
    in  vec2    point)
{
    float value = 1.0;
    value -= min(abs(point.x), abs(point.y)) * mix(4.0, 1.0, armThickness);
    return clamp(value, 0.0, 1.0);
}

vec2 spiral(
    in  vec2    point,
    in  float   factor)
{
    float angle = length(point) * factor;
    angle *= log(length(point * 0.5));

    vec2 rotated;
    rotated.x = point.x * cos(angle) - point.y * sin(angle);
    rotated.y = point.x * sin(angle) + point.y * cos(angle);

    return rotated;
}

void proceduralTexture(
    in  vec2    textureCoords,
    out vec4    outputColor)
{
    vec3 color = vec3(0.0);
    vec2 point = textureCoords - 0.5;

    float value = fractalNoise(vec3(point, seed) * 5.0, 2.4, 0.34, 12) * 0.5 + 0.5;
    value = pow(value, 2.0);

    color += bulgeColor * pow(1.0 - clamp(length(point + value * 0.1) * 2.0, 0.0, 1.0), 10.0) * 2.0;

    float spiralFactor = mix(6.0, 19.0, eccentricity);
    if (seed < 0.0)
    {
        spiralFactor = -spiralFactor;
    }
    vec2 spiraledPoint = spiral(point, spiralFactor);

    float bars = galaxyBar(spiraledPoint + value * 0.08);
    bars = pow(bars, 3.0);

    value *= bars;
    value *= 1.0 - clamp(length(point) * 2.2 + 0.1 * fractalNoise(vec3(point, seed) * 5.0, 2.4, 0.34, 3), 0.0, 1.0);

    color += primaryColor * value * 0.5;

    outputColor = vec4(color, 1.0);
}
