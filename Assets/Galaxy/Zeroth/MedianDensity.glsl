#version 440

uniform float seed;

in vec2 vertexTextureCoords;

out vec4 outputColor;

float fractalNoise(
    in  vec3    point,
    in  float   lacunarity,
    in  float   persistence, 
    in  int     octaveCount);

float galaxyBars(
    in  vec3    point)
{
    float value = 1.0;
    value -= 1.0 - clamp(length(point.y) * 10.0, 0.0, 1.0);
    value -= abs(point.x) * 9.5; // Thin towards middle
    value += abs(point.y) * 4.0; // Thicken towards end
    return clamp(value, 0.0, 1.0);
}

vec3 spiral(
    in  vec3    point,
    in  float   factor)
{
    float d = length(point.xy);
    float angle = d * factor;
    return vec3(point.x * cos(angle) - point.y * sin(angle), point.x * sin(angle) + point.y * cos(angle), point.z);
}

void main()
{
    vec3 point = vec3(vertexTextureCoords.xy - vec2(0.5), seed);
    point = spiral(point * vec3(1.0, 1.2, 1.0), 24.0);

    float value = galaxyBars(point);
    value *= 2.0; // Thicken the bars
    value *= 1.0 - clamp(length(point.xy) * 2.0, 0.0, 1.0); // Falloff towards end
    value = clamp(value, 0.0, 1.0);
    outputColor = vec4(vec3(value), 1.0);
}
