#version 330

uniform sampler2D textureDiffuse;
uniform samplerCube textureCubemap;

uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform vec3 uAmbientLightColor;
uniform vec3 uViewPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive;
    float opacity;
};

layout (std140) uniform ubMaterial {
    Material materials[2];
};

in vec3 vVertex;
in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fragColor;