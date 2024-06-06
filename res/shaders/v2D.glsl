#version 330

in vec2 aVertex;
in vec3 aTexCoord;

out vec3 vTexCoord;

void main() {
	vTexCoord = aTexCoord;
	gl_Position = vec4(aVertex, 0.0, 1.0);
}