//
// Created by dacma on 5/13/2024.
//

#include "UniformBlock.h"

UniformBlock::UniformBlock(Material *material): GlBuffer() {
    GLSL_Material buffer = {
        .ambient = material->ambient,
        .diffuse = material->diffuse,
        .specular = material->specular,
        .emissive = material->emissive,
        .opacity = material->opacity
    };

    bufferData(sizeof(buffer), &buffer);
}

UniformBlock::UniformBlock(const std::vector<Material*> &materials): GlBuffer() {
    auto *buffer = new GLSL_Material[materials.size()];
    for (uint32_t i = 0; i < materials.size(); i++) {
        buffer[i] = {
            .ambient = (materials)[i]->ambient,
            .diffuse = (materials)[i]->diffuse,
            .specular = (materials)[i]->specular,
            .emissive = (materials)[i]->emissive,
            .opacity = (materials)[i]->opacity
        };
        // No additional padding needed since the struct is already a multiple of 16 bytes
    }

    bufferData(sizeof(GLSL_Material) * materials.size(), buffer);
    delete[] buffer;
}

UniformBlock::UniformBlock(GameState::Planet &planet) {
    GLSL_PLANET_PROPS buffer = {
        .liquidHeight = planet.liquidHeight
    };
    bufferData(sizeof(buffer), &buffer);
}

UniformBlock::UniformBlock(const PerlinNoise &perlinNoise) : GlBuffer() {
    GLSL_PERLIN_CONFIG buffer = {
        .numOctaves = perlinNoise.numOctaves,
        .amplitude = perlinNoise.amplitude,
        .frequency = perlinNoise.frequency,
        .amplitudeMult = perlinNoise.amplitudeMult,
        .frequencyMult = perlinNoise.frequencyMult
    };
    for (uint32_t i = 0; i < sizeof(perlinNoise.perm) / sizeof(int); i++) {
        buffer.perm[i*4] = perlinNoise.perm[i];
    }

    bufferData(sizeof(buffer), &buffer);
}

void UniformBlock::setBindingPoint(GLuint index) {
    bind(GL_UNIFORM_BUFFER);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
}
