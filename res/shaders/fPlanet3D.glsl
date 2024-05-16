// include shared/f3D_header.glsl
// include shared/fPhong.glsl

void main() {
    float height = texture(textureCubemap, vVertex).r;
    float liquidHeight = 0.5;
    float liquidTransition = 0.05;
    Material material1 = materials[0];
    Material material2 = materials[1];
    material1.diffuse *= 0.5 + 0.5 * height;
    if (height < liquidHeight - liquidTransition) {
        fragColor = phongShading(material2);
    } else if (height < liquidHeight) {
        float bias1 = ((height - liquidHeight + liquidTransition) / liquidTransition);
        float bias2 = 1.0 - bias1;
        Material material = Material(
            material1.ambient * bias1 + material2.ambient * bias2,
            material1.diffuse * bias1 + material2.diffuse * bias2,
            material1.specular * bias1 + material2.specular * bias2,
            material1.emissive * bias1 + material2.emissive * bias2,
            1.0
        );
        fragColor = phongShading(material);
    } else {
        fragColor = phongShading(material1);
    }
//    fragColor = texture(cubemap, vVertex);

    // fragColor = vec4(fractalMult, fractalMult, fractalMult, 1.0);
    // fragColor = vec4(normal + vec3(0.5, 0.5, 0.5), 1.0);

	// fragColor = vec4((vec2(1.0, 1.0) + vVertex.xy) * 0.5, 1.0, 1.0);
	// fragColor = vec4(vTexCoord, 1.0, 1.0);
	// fragColor = vec4(texture(textureDiffuse, vTexCoord).rgb, 1.0);
}