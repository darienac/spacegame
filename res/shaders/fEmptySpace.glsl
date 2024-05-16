// include shared/f2D_header.glsl
// include shared/perlin.glsl

void main() {
    float fractalMult1 = FractalBrownianMotion((normalize(vTexCoord) + 1.0) * 20.0, perlinConfig) * 0.5 + 0.5;
    float fractalMult2 = FractalBrownianMotion((normalize(vTexCoord.zxy) + 1.0) * 20.0, perlinConfig) * 0.5 + 0.5;
    float fractalMult3 = FractalBrownianMotion((normalize(vTexCoord.yzx) + 1.0) * 20.0, perlinConfig) * 0.5 + 0.5;
    fragColor = vec4(0.068 * fractalMult1, 0.04 * fractalMult2, 0.088 * fractalMult3, 1.0);
//    fragColor = vec4(fractalMult1, fractalMult2, fractalMult3, 1.0);
    // fragColor = vec4((vTexCoord + 1.0) / 2.0, 1.0);
}