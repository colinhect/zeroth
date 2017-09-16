#version 440

uniform mat4 model_view_projection;

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in float vertex_size;

out vec3 galaxy_color;

void main()
{
    gl_Position = model_view_projection * vec4(vertex_position, 1.0);
    gl_PointSize = vertex_size;

    galaxy_color = vertex_color;
}
