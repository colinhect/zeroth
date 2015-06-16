#version 440

uniform float seed;
uniform vec4 bulgeColor;
uniform vec4 primaryColor;
uniform vec4 secondaryColor;
uniform float variation0;
uniform float variation1;
uniform float variation2;
uniform float variation3;

const float bulgeSize = 0.5;

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence, 
    in  int     octaveCount);

float generateBars(
    in  vec2    point)
{
    float value = 1.0;
    value -= min(abs(point.x), abs(point.y)) * mix(4.0, 1.0, variation1);
    return clamp(value, 0.0, 1.0);
}

vec2 spiralPoint(
    in  vec2    point)
{
    float factor = mix(6.0, 19.0, variation0);
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

float desaturate(
    in  vec3    color)
{
    vec3 scaledColor = color * vec3(0.3, 0.59, 0.11);
    return scaledColor.r + scaledColor.g + scaledColor.b;
}

void proceduralTexture(
    in  vec2    textureCoords,
    out vec4    outputColor)
{
    vec3 color = vec3(0.0);
    vec2 point = textureCoords - 0.5;
    vec2 spiraledPoint = spiralPoint(point);

    // Offset noise
    float offsetNoise = fractalNoise(vec3(point, seed) * 5.0 * (variation2 + 1.0), 2.34, 0.42, 8) * 0.5 + 0.5;

    // Ambient noise
    float ambientNoise = fractalNoise(vec3(point, seed) * 5.0, 2.3, 0.35, 12) * 0.5 + 0.5;

    // Center bulge
    color += bulgeColor.rgb * pow(1.0 - clamp(length(point) * 6.0, 0.0, 1.0), 5.0) * 2.0;

    // Bulge halo
    color += bulgeColor.rgb * pow(1.0 - clamp((length(point) + offsetNoise * 0.1) * 2.0, 0.0, 1.0), 10.0) * 2.0;
    
    // Spiral bars
    float spiralBars = generateBars(spiraledPoint + offsetNoise * 0.08);
    spiralBars = pow(spiralBars, 1.34);
    spiralBars *= ambientNoise;
    spiralBars *= 1.0 - clamp(length(point) * 2.2 + 0.1 * fractalNoise(vec3(point, seed) * 5.0, 2.4, 0.34, 3), 0.0, 1.0);
    color += primaryColor.rgb * spiralBars * 0.6;

    // Secondary
    float secondaryNoise = clamp(fractalNoise(vec3(spiraledPoint + offsetNoise * 0.13, seed) * 9.0, 2.2, 0.32, 12) * 0.5 + 0.5, 0.0, 1.0);
    secondaryNoise = pow(secondaryNoise, 3.34);
    color += secondaryColor.rgb * secondaryNoise * spiralBars * 0.5;

    outputColor = vec4(color, desaturate(primaryColor.rgb * spiralBars));
}
