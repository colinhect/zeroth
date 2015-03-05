#version 440

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec2 renderTargetSize;

in float vertexSize[];
in float vertexRotation[];
in float vertexBrightness[];

out vec2 vertexTextureCoords;
out float vertexFinalBrightness;

const vec2 corners[4] =
{ 
    vec2(-0.5, 0.5),
    vec2(-0.5, -0.5),
    vec2(0.5, 0.5),
    vec2(0.5, -0.5)
};

const vec2 textureCoords[4] =
{ 
    vec2(0.0, 1.0),
    vec2(0.0, 0.0),
    vec2(1.0, 1.0),
    vec2(1.0, 0.0)
};

vec2 rotate(
    in  vec2    point,
    in  float   angle)
{
    return vec2(point.x * cos(angle) - point.y * sin(angle), point.x * sin(angle) + point.y * cos(angle));
}

void main()
{
    vec2 aspectRatio = vec2(renderTargetSize.y / renderTargetSize.x, 1.0);

    for (int i = 0; i < 4; ++i)
    {
        vec4 eyePosition = gl_in[0].gl_Position;
        
        eyePosition.xy += rotate(vertexSize[0] * corners[i], vertexRotation[0]) * aspectRatio;
        gl_Position = eyePosition;
        vertexTextureCoords = textureCoords[i];
        vertexFinalBrightness = vertexBrightness[0];
        EmitVertex();
    }

    EndPrimitive();
}
