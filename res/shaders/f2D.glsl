#version 330

uniform sampler2D uTexture;

in vec3 vTexCoord;

out vec4 fragColor;

void main() {
    fragColor = texture(uTexture, vTexCoord.xy);
}