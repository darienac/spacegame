#version 330

uniform mat4 uViewProjectionMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

in vec3 aVertex;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 vVertex;
out vec3 vVertexRotated;
out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;