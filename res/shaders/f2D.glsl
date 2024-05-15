// include shared/f2D_header.glsl

void main() {
    fragColor = texture(uTexture, vTexCoord.xy);
}