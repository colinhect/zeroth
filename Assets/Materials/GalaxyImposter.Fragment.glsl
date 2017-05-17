#version 440

uniform sampler2D spriteTexture;

in vec3 galaxyColor;

out vec4 outputColor;

void main()
{
    outputColor = texture(spriteTexture, gl_PointCoord) * vec4(galaxyColor, 1.0);
}
