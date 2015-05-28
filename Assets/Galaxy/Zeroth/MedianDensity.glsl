#version 440

uniform float spiralFactor;

float galaxyBar(
    in  vec2    point)
{
    float value = 1.0;
    value -= 1.0 - clamp(length(point.y) * 10.0, 0.0, 1.0);

    // Thin towards middle
    value -= abs(point.x) * 9.5;

    // Thicken towards end
    value += abs(point.y) * 4.0;

    return clamp(value, 0.0, 1.0);
}

vec2 spiral(
    in  vec2    point,
    in  float   factor)
{
    float angle = length(point) * factor;

    vec2 rotated;
    rotated.x = point.x * cos(angle) - point.y * sin(angle);
    rotated.y = point.x * sin(angle) + point.y * cos(angle);

    return rotated;
}

void proceduralTexture(
    in  vec3    position,
    out vec4    outputColor)
{
    vec3 point = position * 0.5;

    float value = galaxyBar(spiral(point.xy, spiralFactor));

    // Thicken the bars
    value *= 2.0;

    // Falloff towards end
    value *= 1.0 - clamp(length(point.xy) * 2.0, 0.0, 1.0);
    value = clamp(value, 0.0, 1.0);

    value *= pow(1.0 - clamp(abs(point.z * 8.0), 0.0, 1.0), 2.0);
    
    outputColor = vec4(vec3(value), 1.0);
}
