#version 440

uniform sampler2D galaxyTexture;

in vec3 galaxyColor;

out vec4 outputColor;

void main()
{
    outputColor = texture(galaxyTexture, gl_PointCoord) * vec4(galaxyColor, 1.0);
}
