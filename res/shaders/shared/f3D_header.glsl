#version 330

uniform sampler2D textureDiffuse;
uniform samplerCube cubemap;

uniform vec3 uLightPosition;
uniform vec3 uLightColor;
uniform vec3 uAmbientLightColor;
uniform vec3 uViewPosition;

uniform vec3 uAmbientColor;
uniform vec3 uDiffuseColor;
uniform vec3 uSpecularColor;
uniform vec3 uEmissiveColor;

uniform float uOpacity;

in vec3 vVertex;
in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fragColor;