const float ambientStrength = 1.0;
const float diffuseStrength = 1.0;
const float specularStrength = 1.0;
const float reflectStrength = 0.0;
const float emissiveStrength = 1.0;
const float shininess = 2.0;

vec4 phongShading() {
    vec4 texColor = vec4(uDiffuseColor, 1.0) * texture(textureDiffuse, vTexCoord);

    vec3 normal = normalize(vNormal);
    vec3 lightDirection = normalize(uLightPosition - vPosition);

    vec3 viewDirection = normalize(uViewPosition - vPosition);
    vec3 reflectLightDirection = reflect(-lightDirection, normal);
    // vec3 reflectViewDirection = reflect(-viewDirection, normal);

    vec3 ambientColor = ambientStrength * texColor.rgb;
    vec3 diffuseColor = diffuseStrength * max(0.0, dot(normal, lightDirection)) * texColor.rgb;
    vec3 specularColor = specularStrength * pow(max(dot(viewDirection, reflectLightDirection), 0.0), shininess) * uSpecularColor;
    vec3 emissiveColor = emissiveStrength * uEmissiveColor * texture(textureDiffuse, vTexCoord).rgb;
    // vec3 reflectColor = reflectStrength * texture(textureReflect, reflectViewDirection.xy).rgb;
    vec3 reflectColor = vec3(0.0, 0.0, 0.0);

    return vec4(ambientColor * uAmbientLightColor + (diffuseColor + specularColor + reflectColor) * uLightColor + emissiveColor, texColor.a * uOpacity);
}