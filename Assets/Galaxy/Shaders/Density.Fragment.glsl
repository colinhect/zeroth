#version 440

in vec3 position;

out vec4 outputColor;

void proceduralTexture(
    in  vec3    position,
    out vec4    outputColor);

void main()
{
    proceduralTexture(position, outputColor);
}
