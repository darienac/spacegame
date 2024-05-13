#version 330

uniform mat4 uViewProjectionMatrix;
uniform mat4 uModelMatrix;
uniform mat4 uNormalMatrix;

in vec3 aVertex;
in vec3 aNormal;
in vec2 aTexCoord;

out vec3 vVertex;
out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

void main() {
	vVertex = aVertex;
	vPosition = (uModelMatrix * vec4(aVertex, 1.0)).xyz;
	vNormal = (uNormalMatrix * vec4(aNormal, 1.0)).xyz;
	vTexCoord = aTexCoord;

	gl_Position = uViewProjectionMatrix * vec4(aVertex, 1.0);
}