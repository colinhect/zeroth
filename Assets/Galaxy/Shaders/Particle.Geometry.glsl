#version 440

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec2 renderTargetSize;

in vec3 vertexColor[];
in float vertexSize[];
in float vertexRotation[];

out vec2 vertexTextureCoords;
out vec3 vertexFinalColor;

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
    vec4 position = gl_in[0].gl_Position;

    if (position.z > 500.0)
    {
        float falloff = clamp((position.z - 500.0) * 0.0001, 0.0, 1.0);
        vec2 aspectRatio = vec2(renderTargetSize.y / renderTargetSize.x, 1.0);

        for (int i = 0; i < 4; ++i)
        {
            vec4 eyePosition = position;        
            eyePosition.xy += rotate(vertexSize[0] * corners[i], vertexRotation[0]) * aspectRatio;
            gl_Position = eyePosition;
            vertexTextureCoords = textureCoords[i];
            vertexFinalColor = vertexColor[0] * falloff;
            EmitVertex();
        }

        EndPrimitive();
    }
}
