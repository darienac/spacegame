const float ambientStrength = 1.0;
const float diffuseStrength = 1.0;
const float specularStrength = 1.0;
const float reflectStrength = 0.0;
const float emissiveStrength = 1.0;
const float shininess = 30.0;

vec4 phongShading(Material material, Light light, vec3 modelPos, vec3 viewPos, vec3 modelNorm) {
    vec4 texColor = vec4(material.diffuse, 1.0);

    vec3 normal = normalize(modelNorm);
    vec3 viewDirection = normalize(viewPos - modelPos);
    // vec3 reflectViewDirection = reflect(-viewDirection, normal);
    vec3 ambientColor = ambientStrength * texColor.rgb;
    vec3 emissiveColor = emissiveStrength * material.emissive;

    vec3 diffuseColor = vec3(0.0f, 0.0f, 0.0f);
    vec3 specularColor = vec3(0.0f, 0.0f, 0.0f);
    for (uint i = 0u; i < light.numLightSources; i++) {
        vec3 lightDirection = normalize(light.lightSources[i].position - modelPos);
        vec3 reflectLightDirection = reflect(-lightDirection, normal);

        diffuseColor += diffuseStrength * max(0.0, dot(normal, lightDirection)) * texColor.rgb * light.lightSources[i].color;
        specularColor += specularStrength * pow(max(dot(viewDirection, reflectLightDirection), 0.0), shininess) * material.specular * light.lightSources[i].color;
    }
    // vec3 emissiveColor = vec3(0.0, 0.0, 0.0);
    // vec3 reflectColor = reflectStrength * texture(textureReflect, reflectViewDirection.xy).rgb;
    vec3 reflectColor = vec3(0.0, 0.0, 0.0);

    return vec4(ambientColor * light.ambientLightColor + (diffuseColor + specularColor + reflectColor) + emissiveColor, texColor.a * material.opacity);
}

vec4 phongShading(Material material, Light light) {
    return phongShading(material, light, vPosition, uViewPosition, vNormal);
}