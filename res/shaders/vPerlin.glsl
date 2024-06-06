#version 330

uniform mat4 uTexCoordTransform;

in vec2 aVertex;
in vec3 aTexCoord;

out vec3 vTexCoord;

void main() {
    vTexCoord = (uTexCoordTransform * vec4(aTexCoord, 1.0)).xyz;
    gl_Position = vec4(aVertex, 0.0, 1.0);
}