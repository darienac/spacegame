struct PerlinConfig {
    int perm[256];
    int numOctaves;
    float amplitude;
    float frequency;
    float amplitudeMult;
    float frequencyMult;
};

layout (std140) uniform ubPerlinConfig {
    PerlinConfig perlinConfig;
};

vec3 getConstantVector(int i) {
    int v = i & 7;
    switch (v) {
        case 0:
            return vec3(1.0, 1.0, -1.0);
        case 1:
            return vec3(-1.0, 1.0, -1.0);
        case 2:
            return vec3(-1.0, -1.0, -1.0);
        case 3:
            return vec3(1.0, -1.0, -1.0);
        case 4:
            return vec3(1.0, -1.0, 1.0);
        case 5:
            return vec3(-1.0, -1.0, 1.0);
        case 6:
            return vec3(-1.0, 1.0, 1.0);
        case 7:
            return vec3(1.0, 1.0, 1.0);
    }
}

float Lerp(float t, float a1, float a2) {
    return a1 + t*(a2-a1);
}

float Fade(float t) {
    return ((6.0*t - 15.0)*t + 10.0)*t*t*t;
}

float Noise3D(float x, float y, float z, PerlinConfig c) {
    int X = int(x) & 255;
    int Y = int(y) & 255;
    int Z = int(z) & 255;
    float xf = x-floor(x);
    float yf = y-floor(y);
    float zf = z-floor(z);

    vec3 topRightFront = vec3(xf-1.0, yf-1.0, zf-1.0);
    vec3 topLeftFront = vec3(xf, yf-1.0, zf-1.0);
    vec3 bottomRightFront = vec3(xf-1.0, yf, zf-1.0);
    vec3 bottomLeftFront = vec3(xf, yf, zf-1.0);
    vec3 topRightBack = vec3(xf-1.0, yf-1.0, zf);
    vec3 topLeftBack = vec3(xf, yf-1.0, zf);
    vec3 bottomRightBack = vec3(xf-1.0, yf, zf);
    vec3 bottomLeftBack = vec3(xf, yf, zf);

    vec3 valueTopRightFront = getConstantVector(c.perm[(c.perm[(c.perm[(X+1)&255]+Y+1)&255]+Z+1)&255]);
    vec3 valueTopLeftFront = getConstantVector(c.perm[(c.perm[(c.perm[X]+Y+1)&255]+Z+1)&255]);
    vec3 valueBottomRightFront = getConstantVector(c.perm[(c.perm[(c.perm[(X+1)&255]+Y)&255]+Z+1)&255]);
    vec3 valueBottomLeftFront = getConstantVector(c.perm[(c.perm[(c.perm[X]+Y)&255]+Z+1)&255]);
    vec3 valueTopRightBack = getConstantVector(c.perm[(c.perm[(c.perm[(X+1)&255]+Y+1)&255]+Z)&255]);
    vec3 valueTopLeftBack = getConstantVector(c.perm[(c.perm[(c.perm[X]+Y+1)&255]+Z)&255]);
    vec3 valueBottomRightBack = getConstantVector(c.perm[(c.perm[(c.perm[(X+1)&255]+Y)&255]+Z)&255]);
    vec3 valueBottomLeftBack = getConstantVector(c.perm[(c.perm[(c.perm[X]+Y)&255]+Z)&255]);

    float dotTopRightFront = dot(topRightFront, valueTopRightFront);
    float dotTopLeftFront = dot(topLeftFront, valueTopLeftFront);
    float dotBottomRightFront = dot(bottomRightFront, valueBottomRightFront);
    float dotBottomLeftFront = dot(bottomLeftFront, valueBottomLeftFront);
    float dotTopRightBack = dot(topRightBack, valueTopRightBack);
    float dotTopLeftBack = dot(topLeftBack, valueTopLeftBack);
    float dotBottomRightBack = dot(bottomRightBack, valueBottomRightBack);
    float dotBottomLeftBack = dot(bottomLeftBack, valueBottomLeftBack);

    float u = Fade(xf);
    float v = Fade(yf);
    float w = Fade(zf);

    float z1 = Lerp(u,
                    Lerp(v, dotBottomLeftBack, dotTopLeftBack),
                    Lerp(v, dotBottomRightBack, dotTopRightBack)
    );

    float z2 = Lerp(u,
                    Lerp(v, dotBottomLeftFront, dotTopLeftFront),
                    Lerp(v, dotBottomRightFront, dotTopRightFront)
    );

    return Lerp(w, z1, z2);
}

float FractalBrownianMotion(vec3 value, PerlinConfig c) {
    float result = 0.0;
    float amplitude = c.amplitude;
    float frequency = c.frequency; // was 0.005

    for (int octave = 0; octave < c.numOctaves; octave++) {
        float n = amplitude * Noise3D(value.x * frequency, value.y * frequency, value.z * frequency, c);
        result += n;

        amplitude *= c.amplitudeMult; // was 0.5, 0.25 works better for smoother terrain
        frequency *= c.frequencyMult;
    }

    return result;
}