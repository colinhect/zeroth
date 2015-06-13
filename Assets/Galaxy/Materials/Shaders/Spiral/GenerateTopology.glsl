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

float generateBars(
    in  vec2    point)
{
    float value = 1.0;
    value -= min(abs(point.x), abs(point.y)) * mix(4.0, 1.0, armThickness);
    return clamp(value, 0.0, 1.0);
}

vec2 spiralPoint(
    in  vec2    point)
{
    float factor = mix(6.0, 19.0, eccentricity);
    if (seed < 0.0)
    {
        factor = -factor;
    }

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
    vec2 spiraledPoint = spiralPoint(point);

    // Offset noise
    float offsetNoise = fractalNoise(vec3(point, seed) * 5.0, 2.34, 0.42, 8) * 0.5 + 0.5;

    // Ambient noise
    float ambientNoise = fractalNoise(vec3(point, seed) * 5.0, 2.4, 0.34, 12) * 0.5 + 0.5;
    ambientNoise = pow(ambientNoise, 2.0);

    // Center bulge
    color += bulgeColor * pow(1.0 - clamp(length(point) * 6.0, 0.0, 1.0), 5.0) * 2.0;

    // Bulge halo
    color += bulgeColor * pow(1.0 - clamp((length(point) + offsetNoise * 0.1) * 2.0, 0.0, 1.0), 10.0) * 2.0;
    
    // Spiral bars
    float spiralBars = generateBars(spiraledPoint + offsetNoise * 0.08);
    spiralBars = pow(spiralBars, 2.34);
    spiralBars *= ambientNoise;
    spiralBars *= 1.0 - clamp(length(point) * 2.2 + 0.1 * fractalNoise(vec3(point, seed) * 5.0, 2.4, 0.34, 3), 0.0, 1.0);
    color += primaryColor * spiralBars * 0.25;

    outputColor = vec4(color, 1.0);
}
