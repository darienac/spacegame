struct PlanetProps {
    vec4 atmosphereColor;
    float radius;
    float atmosphereRadiusFilled;
    float liquidHeight;
};

layout (std140) uniform ubPlanetProps {
    PlanetProps planetProps;
};