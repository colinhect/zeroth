#version 410

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
    return fractalNoise(point, 2.0, 0.5, 6) - sin(point.x * 2.0) * 2.5;
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
    point = spiral(point * vec3(1.0, 1.2, 1.0), 8.0) ;
    float value = galaxyBars(point * 10.0) * 0.5 + 0.5;
    value *= 1.0 - clamp(length(point.xy) * 2.0, 0.0, 1.0);
    value += 1.0 - clamp(length(point.xy) * 6.0, 0.0, 1.0);
    value = clamp(value, 0.0, 1.0);
    outputColor = vec4(vec3(value), 1.0);
}
