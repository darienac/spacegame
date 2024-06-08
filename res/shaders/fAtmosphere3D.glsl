Material mat = Material(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), 1.0, 0.0);

void main() {
    vec3 viewDirection = normalize(vPosition - uViewPosition);
    vec3 normal = normalize(uViewPosition - uModelPosition);
    bool aboveHorizon = dot(viewDirection, normal) > 0.0;
    if (aboveHorizon) {
        viewDirection -= dot(viewDirection, normal) * normal;
    }
    vec3 viewNormal = normalize(dot(viewDirection, uModelPosition - uViewPosition) * viewDirection - (uModelPosition - uViewPosition));
    float distToCenter;
    if (aboveHorizon) {
        distToCenter = length(uViewPosition - uModelPosition) * planetProps.atmosphereRadiusFilled / planetProps.radius;
    } else {
        distToCenter = dot(viewNormal, vPosition - uModelPosition) * planetProps.atmosphereRadiusFilled / planetProps.radius;
    }
    float opacity = clamp(1.0 - (distToCenter - planetProps.atmosphereRadiusFilled) / (1.0 - planetProps.atmosphereRadiusFilled), 0.0, 1.0);

    fragColor = vec4(phongShading(mat, light).rgb * planetProps.atmosphereColor.rgb, planetProps.atmosphereColor.a * opacity);
}