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
    
    float value = fractalNoise(point * 5.0, 2.0, 0.5, 6) * 0.2 + 0.8;
    value *= pow(1.0 - clamp(length(point.xy) * 2.0, 0.0, 1.0), 2.0);
    value = clamp(value, 0.0, 1.0);

    outputColor = color * value;
}
