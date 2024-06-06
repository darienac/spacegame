// include shared/f2D_header.glsl
// include shared/perlin.glsl

void main() {
    float fractalMult = FractalBrownianMotion((normalize(vTexCoord) + 1.0) * 20.0, perlinConfig) * 0.5 + 0.5;
    fragColor = vec4(fractalMult, fractalMult, fractalMult, 1.0);
//     fragColor = vec4((vTexCoord + 1.0) / 2.0, 1.0);
//    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}