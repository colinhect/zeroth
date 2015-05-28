#version 440

layout(points) in;
layout(points, max_vertices = 1) out;

in int vertexLayer[];

out vec3 position;

void main()
{
    vec4 pointPosition = gl_in[0].gl_Position;
    position = pointPosition.xyz;

    gl_Position = vec4(position.xy, 0.0, 1.0);
    gl_Layer = vertexLayer[0];

    EmitVertex();
    EndPrimitive();
}
