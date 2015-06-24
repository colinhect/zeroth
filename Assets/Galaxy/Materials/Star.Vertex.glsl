#version 440

uniform vec3 cameraPosition;
uniform mat4 model;
uniform mat4 modelViewProjection;
uniform vec2 sizeRange;
uniform vec2 brightnessRange;

layout(location = 0) in vec3 position;
layout(location = 1) in float size;
layout(location = 2) in float brightness;
layout(location = 3) in float distance;

const vec3 colors[4] = vec3[4](
    vec3(1.0, 0.3, 0.3),
    vec3(1.0, 1.0, 0.6),
    vec3(1.0, 1.0, 1.0),
    vec3(0.4, 0.4, 1.0)
);

out vec3 starColor;

void main()
{
    gl_Position = modelViewProjection * vec4(position, 1.0);

    starColor = mix(colors[0], colors[1], smoothstep(0.0, 0.3, size));
    starColor = mix(starColor, colors[2], smoothstep(0.3, 0.6, size));
    starColor = mix(starColor, colors[3], smoothstep(0.6, 1.0, size));

    vec3 worldPosition = (model * vec4(position, 1.0)).xyz;
    float distanceFalloff = 1.0 - clamp(clamp(length(worldPosition - cameraPosition), 0.0, distance) / distance, 0.0, 1.0);

    gl_PointSize = mix(0.0, mix(sizeRange.x, sizeRange.y, size), distanceFalloff);

    float starBrightness = mix(brightnessRange.x, brightnessRange.y, brightness);
    starBrightness *= pow(distanceFalloff, 4.0);

    starColor *= starBrightness;
}