// include shared/f3D_header.glsl
// include shared/fPhong.glsl

void main() {
    fragColor = phongShading(material) * texture(cubemap, vVertex);
//    fragColor = texture(cubemap, vVertex);

    // fragColor = vec4(fractalMult, fractalMult, fractalMult, 1.0);
    // fragColor = vec4(normal + vec3(0.5, 0.5, 0.5), 1.0);

	// fragColor = vec4((vec2(1.0, 1.0) + vVertex.xy) * 0.5, 1.0, 1.0);
	// fragColor = vec4(vTexCoord, 1.0, 1.0);
	// fragColor = vec4(texture(textureDiffuse, vTexCoord).rgb, 1.0);
}