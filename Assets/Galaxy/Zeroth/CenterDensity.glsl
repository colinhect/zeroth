#version 440

void proceduralTexture(
    in  vec2    textureCoords,
    out vec4    outputColor)
{
    vec2 point = textureCoords - 0.5;

    float value = 1.0 - clamp(length(point) * 12.0, 0.0, 1.0);
    outputColor = vec4(vec3(value), 1.0);
}
