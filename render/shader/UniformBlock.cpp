//
// Created by dacma on 5/13/2024.
//

#include "UniformBlock.h"

UniformBlock::UniformBlock(UniformBlock::BindingPoint type) {
    // block only created with a specified size, so needs to be rewritten later
    GLsizeiptr size;
    switch (type) {
        case MATERIAL:
            size = sizeof(GLSL_MATERIAL);
            break;
        case LIGHT:
            size = sizeof(GLSL_LIGHT);
            break;
        case PLANET_PROPS:
            size = sizeof(GLSL_PLANET_PROPS);
            break;
        case PERLIN_CONFIG:
            size = sizeof(GLSL_PERLIN_CONFIG);
            break;
        default:
            throw std::runtime_error("Unsupported uniform block type");
    }
    char *buffer = new char[size]; // I don't really care what data is put in here, just allocating the memory needed
    bufferData(size, buffer, GL_DYNAMIC_DRAW);
    delete[] buffer;
}

UniformBlock::UniformBlock(Material *material): GlBuffer() {
    GLSL_MATERIAL buffer = {
        .ambient = material->ambient,
        .diffuse = material->diffuse,
        .specular = material->specular,
        .emissive = material->emissive,
        .opacity = material->opacity
    };

    bufferData(sizeof(buffer), &buffer, GL_DYNAMIC_DRAW);
}

UniformBlock::UniformBlock(const std::vector<Material*> &materials): GlBuffer() {
    auto *buffer = new GLSL_MATERIAL[materials.size()];
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

    bufferData(sizeof(GLSL_MATERIAL) * materials.size(), buffer);
    delete[] buffer;
}

UniformBlock::UniformBlock(GameState::Planet &planet) {
    GLSL_PLANET_PROPS buffer = {
        .atmosphereColor = planet.atmosphereColor,
        .radius = planet.radius,
        .atmosphereRadiusFilled = planet.radius / (planet.atmosphereHeight + planet.radius),
        .liquidHeight = planet.liquidHeight,
        .maxLandHeight = planet.maxLandHeight
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

void UniformBlock::loadMaterial(Material *material) {
    GLSL_MATERIAL buffer = {
            .ambient = material->ambient,
            .diffuse = material->diffuse,
            .specular = material->specular,
            .emissive = material->emissive,
            .opacity = material->opacity
    };

    subData(sizeof(buffer), &buffer);
}

void UniformBlock::loadLights(const std::vector<GameState::Light*> &lights, const glm::vec3 &ambientLight) {
    GLSL_LIGHT buffer = {
            .numLightSources = (uint32_t) lights.size(),
            .ambientLightColor = ambientLight
    };
    if (buffer.numLightSources > MAX_LIGHTS) {
        buffer.numLightSources = MAX_LIGHTS;
    }
    for (uint32_t i = 0; i < buffer.numLightSources; i++) {
        buffer.lightSources[i] = {
                .position = lights[i]->position,
                .color = lights[i]->color
        };
    }

    subData(sizeof(buffer), &buffer);
}

void UniformBlock::setBindingPoint(GLuint index) {
    bind(GL_UNIFORM_BUFFER);
    glBindBufferBase(GL_UNIFORM_BUFFER, index, id);
}
