#version 440

uniform float seed;

float simplexNoise(
    in  vec3    point);

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence,
    in  int     octaveCount);

float random(
    in  float   seed,
    in  float   min,
    in  float   max);

const float barThickness = random(seed, 1.0, 8.0);
const float spiralFactor = random(seed, 3.0, 18.0);

const float weights[32] = float[32](
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0),
    random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0)
);

const vec3 colors[4] = vec3[4](
    vec3(random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0)),
    vec3(random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0)),
    vec3(random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0)),
    vec3(random(seed, 0.0, 1.0), random(seed, 0.0, 1.0), random(seed, 0.0, 1.0))
);

float generateBars(
    in  vec2    point)
{
    float value = 1.0;
    value -= min(abs(point.x), abs(point.y)) * barThickness;
    return clamp(value, 0.0, 1.0);
}

vec2 spiralPoint(
    in  vec2    point)
{
    float factor = spiralFactor;
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
    float offsetNoise = fractalNoise(vec3(point, seed) * mix(weights[0], 4.0, 6.0), 2.34, 0.42, 8);
    offsetNoise = clamp(offsetNoise * 0.5 + 0.5, 0.0, 1.0);

    // Ambient noise
    float ambientNoise = fractalNoise(vec3(point, seed) * mix(weights[1], 2.0, 4.0), 2.3, 0.35, 12);
    ambientNoise = clamp(ambientNoise * 0.5 + 0.5, 0.0, 1.0);

    // Bulge noise
    float bulgeNoise = fractalNoise(vec3(point, seed) * mix(weights[2], 2.0, 3.0), 2.3, 0.35, 6);
    bulgeNoise = clamp(bulgeNoise * 0.5 + 0.5, 0.0, 1.0);

    // Center bulge
    color += colors[0] * pow(1.0 - clamp(length(point) * mix(weights[3], 1.5, 6.0), 0.0, 1.0), 5.0) * 2.0;

    // Bulge halo
    color += colors[0] * bulgeNoise * pow(1.0 - clamp(length(point) * mix(weights[4], 1.0, 2.5), 0.0, 1.0), 10.0) * 2.0;
    
    // Spiral bars
    float spiralBars = generateBars(spiraledPoint + offsetNoise * 0.08);
    spiralBars = pow(spiralBars, 2.34);
    spiralBars *= ambientNoise;
    spiralBars *= 1.0 - clamp(length(point) * 2.2 + 0.1 * fractalNoise(vec3(point, seed) * 5.0, 2.4, 0.34, 3), 0.0, 1.0);
    color += colors[1] * spiralBars * 0.6;

    // Secondary
    float secondaryNoise = clamp(fractalNoise(vec3(spiraledPoint + offsetNoise * 0.13, seed) * 9.0, 2.2, 0.32, 12) * 0.5 + 0.5, 0.0, 1.0);
    secondaryNoise = pow(secondaryNoise, 3.34);
    color += colors[2] * secondaryNoise * spiralBars * 0.25;

    // Tertiary
    float tartiaryNoise = clamp(fractalNoise(vec3(spiraledPoint + offsetNoise * 0.3, seed) * 10.0, 2.2, 0.32, 12) * 0.5 + 0.5, 0.0, 1.0);
    tartiaryNoise = pow(tartiaryNoise, 4.34);
    color += colors[3] * tartiaryNoise * spiralBars * 0.15;

    float thickness = max(color.r, max(color.g, color.b));
    outputColor = vec4(color, thickness);
    //outputColor = vec4(generateBars(point));
}
