#version 440

in vec2 vertexTextureCoords;

out vec4 outputColor;

void proceduralTexture(
    in  vec2    textureCoords,
    out vec4    outputColor);

void main()
{
    proceduralTexture(vertexTextureCoords, outputColor);
}
