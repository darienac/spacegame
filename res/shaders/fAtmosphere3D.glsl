Material mat = Material(vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 0.0), 1.0);

void main() {
    vec3 viewDirection = normalize(vPosition - uViewPosition);
    float centerDist;
    bool inAtmosphere = dot(uViewPosition - uModelPosition, viewDirection) > 0.0;
    if (inAtmosphere) {
        centerDist = length(uViewPosition - uModelPosition) / 1.015;
    } else {
        vec3 p1 = normalize(vVertexRotated);
        vec3 p2 = p1 - 2*dot(p1, viewDirection)* viewDirection;
        centerDist = length((p2+p1)/2.0);
    }
    float opacity = clamp(1.0 - (centerDist - planetProps.atmosphereRadiusFilled) / (1.0 - planetProps.atmosphereRadiusFilled), 0.0, 1.0);
//    if (opacity == 1.0 && !inAtmosphere) {
//        opacity = 0.1;
//    }
    fragColor = vec4(phongShading(mat, light).rgb * planetProps.atmosphereColor.rgb, planetProps.atmosphereColor.a * opacity);
//    fragColor = planetProps.atmosphereColor * distTravelled/2.0;
//    fragColor = vec4(1.0, 1.0, 1.0, 1.0) * distTravelled/2.0;
//    fragColor = vec4(1.0, 1.0, 1.0, 0.2);
}