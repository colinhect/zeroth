#version 440

uniform sampler2D sprite_texture;

in vec3 galaxy_color;

out vec4 output_color;

void main()
{
    output_color = texture(sprite_texture, gl_PointCoord) * vec4(galaxy_color, 1.0);
}
