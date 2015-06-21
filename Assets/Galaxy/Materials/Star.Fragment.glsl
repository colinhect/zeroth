#version 440

uniform sampler2D starTexture;

in vec3 starColor;

out vec4 outputColor;

void main()
{
    outputColor = texture(starTexture, gl_PointCoord) * vec4(starColor, 1.0);
}