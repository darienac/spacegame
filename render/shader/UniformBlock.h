//
// Created by dacma on 5/13/2024.
//

#ifndef SPACEGAME_UNIFORMBLOCK_H
#define SPACEGAME_UNIFORMBLOCK_H


#include "../GlBuffer.h"
#include "../model/Material.h"
#include "../../game/state/GameState.h"

class UniformBlock: public GlBuffer {
private:
    struct GLSL_Material {
        glm::vec3 ambient;
        float padding1;
        glm::vec3 diffuse;
        float padding2;
        glm::vec3 specular;
        float padding3;
        glm::vec3 emissive;
        float opacity;
    };

    struct GLSL_PLANET_PROPS {
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
        PLANET_PROPS,
        PERLIN_CONFIG
    };
    explicit UniformBlock(Material* material);
    explicit UniformBlock(const std::vector<Material*> &materials);

    explicit UniformBlock(GameState::Planet &planet);

    explicit UniformBlock(const PerlinNoise &perlinNoise);

    void setBindingPoint(GLuint index);
};


#endif //SPACEGAME_UNIFORMBLOCK_H
