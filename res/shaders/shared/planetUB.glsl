struct PlanetProps {
    vec4 atmosphereColor;
    float atmosphereRadiusFilled;
    float liquidHeight;
};

layout (std140) uniform ubPlanetProps {
    PlanetProps planetProps;
};