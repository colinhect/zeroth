#version 440

void proceduralTexture(
    in  vec3    position,
    out vec4    outputColor)
{
    vec3 point = position * 0.5;
    point.z *= 0.5;

    float value = 1.0 - clamp(length(point) * 12.0, 0.0, 1.0);
    outputColor = vec4(vec3(value), 1.0);
}
