#version 440

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 viewProjection;
uniform vec3 cameraPosition;

in vec3 vertexColor[];
in float vertexSize[];
in float vertexRotation[];

out vec2 vertexTextureCoords;
out vec3 vertexFinalColor;

const vec2 textureCoords[4] =
{ 
    vec2(0.0, 1.0),
    vec2(0.0, 0.0),
    vec2(1.0, 1.0),
    vec2(1.0, 0.0)
};

mat3 rotationMatrix(
    in  vec3    axis,
    in  float   angle)
{
    axis = normalize(axis);

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;
    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;
    
    return mat3(
        oc * x * x + c, oc * x * y - z * s, oc * z * x + y * s,
        oc * x * y + z * s, oc * y * y + c, oc * y * z - x * s,
        oc * z * x - y * s, oc * y * z + x * s, oc * z * z + c);
}

void main()
{
    vec3 position = gl_in[0].gl_Position.xyz;
    vec3 cameraDirection = cameraPosition - position;
    vec3 right = normalize(cross(cameraDirection, vec3(0.0, 0.0, 1.0)));
    vec3 up = normalize(cross(cameraDirection, right));

    mat3 rotation = rotationMatrix(cameraDirection, vertexRotation[0]);
    right = rotation * right;
    up = rotation * up;

    float halfSize = vertexSize[0] * 0.5;

    vec3 positions[4] =
    {
        position - right * halfSize + up * halfSize,
        position - right * halfSize - up * halfSize,
        position + right * halfSize + up * halfSize,
        position + right * halfSize - up * halfSize
    };

    for (int i = 0; i < 4; ++i)
    {
        gl_Position = viewProjection * vec4(positions[i], 1.0);
        vertexTextureCoords = textureCoords[i];
        vertexFinalColor = vertexColor[0];
        EmitVertex();
    }

    EndPrimitive();
}
