//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_UNIFORMBLOCK_H
#define SPACEGAME_UNIFORMBLOCK_H


#include "../GlBuffer.h"
#include "../model/Material.h"
#include "../../game/state/GameState.h"
#include "glm/vec4.hpp"

class UniformBlock: public GlBuffer {
private:
    static const uint32_t MAX_LIGHTS = 8;

    struct GLSL_MATERIAL {
        glm::vec3 ambient;
        float padding1;
        glm::vec3 diffuse;
        float padding2;
        glm::vec3 specular;
        float padding3;
        glm::vec3 emissive;
        float opacity;
    };

    struct GLSL_LIGHT_SOURCE {
        glm::vec3 position;
        float padding1;
        glm::vec3 color;
        float padding2;
    };

    struct GLSL_LIGHT {
        GLSL_LIGHT_SOURCE lightSources[MAX_LIGHTS];
        uint32_t numLightSources;
        glm::vec3 padding;
        glm::vec3 ambientLightColor;
    };

    struct GLSL_PLANET_PROPS {
        glm::vec4 atmosphereColor;
        float atmosphereRadiusFilled;
        float liquidHeight;
    };

    struct GLSL_PERLIN_CONFIG {
        int perm[256 * 4];
        int numOctaves;
        float amplitude;
        float frequency;
        float amplitudeMult;
        float frequencyMult;
    };
public:
    enum BindingPoint {
        MATERIAL,
        LIGHT,
        PLANET_PROPS,
        PERLIN_CONFIG
    };
    explicit UniformBlock(BindingPoint type);
    explicit UniformBlock(Material* material);
    explicit UniformBlock(const std::vector<Material*> &materials);

    explicit UniformBlock(GameState::Planet &planet);

    explicit UniformBlock(const PerlinNoise &perlinNoise);

    void loadLights(const std::vector<GameState::Light*> &lights, const glm::vec3 &ambientLight);
    void setBindingPoint(GLuint index);
};


#endif //SPACEGAME_UNIFORMBLOCK_H
