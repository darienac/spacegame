vec4 getPlanetSurfaceColor(in float noiseVal, in PlanetProps planetProps) {
    float liquidHeight = planetProps.liquidHeight;
    float landHeight = planetProps.maxLandHeight * noiseVal;
    float liquidTransition = 0.01 * planetProps.maxLandHeight;
    Material material1 = materials[0];
    Material material2 = materials[1];
    material1.diffuse *= 0.5 + 0.5 * noiseVal;
    if (landHeight < liquidHeight - liquidTransition) {
        return phongShading(material2, light);
    } else if (landHeight < liquidHeight) {
        float bias1 = ((landHeight - liquidHeight + liquidTransition) / liquidTransition);
        float bias2 = 1.0 - bias1;
        Material material = Material(
            material1.ambient * bias1 + material2.ambient * bias2,
            material1.diffuse * bias1 + material2.diffuse * bias2,
            material1.specular * bias1 + material2.specular * bias2,
            material1.emissive * bias1 + material2.emissive * bias2,
            1.0,
            material1.glossiness * bias1 + material2.glossiness * bias2
        );
        return phongShading(material, light);
    } else {
        return phongShading(material1, light);
    }
}