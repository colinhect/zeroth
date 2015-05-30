#version 440

uniform sampler2D starTexture;

in float vertexBrightness;

out vec4 outputColor;

void main()
{
    outputColor = texture(starTexture, gl_PointCoord) * vertexBrightness;
}