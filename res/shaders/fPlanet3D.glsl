// include shared/f3D_header.glsl
// include shared/planetUB.glsl
// include shared/fPhong.glsl

void main() {
    fragColor = getPlanetSurfaceColor(texture(textureCubemap, vVertex).r, planetProps);
}