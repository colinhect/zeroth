#version 440

uniform vec3 cameraPosition;
uniform vec3 topologyNormal;
uniform sampler2D topologyTexture;
uniform float brightness;

in vec3 vertexPosition;
in vec2 vertexTextureCoords;

const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;

bool renderStage(
    out vec4    outColor)
{
    // Fade away topology when looking at the galaxy from the side
    float angularFalloff = abs(acos(dot(normalize(cameraPosition), normalize(topologyNormal))));
    angularFalloff = abs(PI_2 - angularFalloff) / PI_2;   
 
    // Fade away topology details close to the camera
    float distanceFalloff = clamp((length(vertexPosition) - 10000.0) * 0.00001, 0.0, 1.0);
    const float falloff = angularFalloff * distanceFalloff;

    outColor = texture(topologyTexture, vertexTextureCoords) * brightness * falloff;
    return true;
}
