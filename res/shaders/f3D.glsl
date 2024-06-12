// include shared/f3D_header.glsl
// include shared/fPhong.glsl

void main() {
    Material material = materials[0];
    material.diffuse *= texture(textureDiffuse, vTexCoord);
    fragColor = phongShading(material, light) + texture(textureCubemap, reflect(vPosition - uViewPosition, vNormal)) * vec4(material.specular, 1.0);
    // fragColor = vec4(normal + vec3(0.5, 0.5, 0.5), 1.0);

	// fragColor = vec4((vec2(1.0, 1.0) + vVertex.xy) * 0.5, 1.0, 1.0);
	// fragColor = vec4(vTexCoord, 1.0, 1.0);
	// fragColor = vec4(texture(textureDiffuse, vTexCoord).rgb, 1.0);
}