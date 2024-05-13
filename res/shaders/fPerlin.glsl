#version 330

uniform sampler2D uTexture;

in vec3 vTexCoord;

out vec4 fragColor;

int PERM[256] = int[](149,142,120,125,178,21,129,250,26,3,53,180,168,253,218,177,27,30,158,75,32,117,222,56,195,39,69,71,44,160,143,199,201,102,19,251,165,184,154,70,115,249,153,52,28,78,121,220,95,7,183,72,10,107,179,188,57,99,215,144,225,155,47,68,235,37,40,74,136,85,84,55,204,243,202,217,67,187,227,211,174,219,134,233,6,18,77,92,166,24,66,161,14,9,49,192,89,106,98,36,105,13,148,35,79,103,45,186,230,164,65,207,138,203,221,132,175,238,131,111,15,255,212,23,5,46,90,237,198,209,83,150,216,196,76,157,224,254,87,245,34,137,127,152,11,241,130,113,141,171,17,169,173,172,210,234,94,252,206,88,43,12,20,242,41,176,162,2,112,22,247,73,4,29,189,182,240,109,63,228,51,246,123,97,42,140,200,48,33,96,64,236,193,159,151,146,133,1,0,226,139,248,54,118,128,223,163,167,116,58,8,185,25,190,147,108,126,194,59,16,191,244,145,229,170,38,91,124,100,31,81,119,61,231,156,104,86,232,197,205,101,214,60,239,135,82,122,208,80,93,213,110,62,114,181,50);

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

float Noise3D(float x, float y, float z) {
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

    vec3 valueTopRightFront = getConstantVector(PERM[(PERM[(PERM[(X+1)&255]+Y+1)&255]+Z+1)&255]);
    vec3 valueTopLeftFront = getConstantVector(PERM[(PERM[(PERM[X]+Y+1)&255]+Z+1)&255]);
    vec3 valueBottomRightFront = getConstantVector(PERM[(PERM[(PERM[(X+1)&255]+Y)&255]+Z+1)&255]);
    vec3 valueBottomLeftFront = getConstantVector(PERM[(PERM[(PERM[X]+Y)&255]+Z+1)&255]);
    vec3 valueTopRightBack = getConstantVector(PERM[(PERM[(PERM[(X+1)&255]+Y+1)&255]+Z)&255]);
    vec3 valueTopLeftBack = getConstantVector(PERM[(PERM[(PERM[X]+Y+1)&255]+Z)&255]);
    vec3 valueBottomRightBack = getConstantVector(PERM[(PERM[(PERM[(X+1)&255]+Y)&255]+Z)&255]);
    vec3 valueBottomLeftBack = getConstantVector(PERM[(PERM[(PERM[X]+Y)&255]+Z)&255]);

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

float FractalBrownianMotion(vec3 value, int numOctaves) {
    float result = 0.0;
    float amplitude = 1.0;
    float frequency = 0.2; // was 0.005

    for (int octave = 0; octave < numOctaves; octave++) {
        float n = amplitude * Noise3D(value.x * frequency, value.y * frequency, value.z * frequency);
        result += n;

        amplitude *= 0.25; // was 0.5, 0.25 works better for smoother terrain
        frequency *= 2.0;
    }

    return result;
}

void main() {
    float fractalMult = FractalBrownianMotion((normalize(vTexCoord) + 1.0) * 20.0, 2) * 0.5 + 0.5;
    fragColor = vec4(fractalMult, fractalMult, fractalMult, 1.0);
    // fragColor = vec4((vTexCoord + 1.0) / 2.0, 1.0);
}