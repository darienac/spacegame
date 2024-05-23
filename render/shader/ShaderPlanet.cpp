//
// Created by dacma on 5/14/2024.
//

#include "ShaderPlanet.h"
#include "UniformBlock.h"

ShaderPlanet::ShaderPlanet(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader): Shader3D(vertexShader, fragmentShader) {
    ubPlanetProps = uniformBlock("ubPlanetProps", UniformBlock::PLANET_PROPS);
}

void ShaderPlanet::drawPlanet(GameState::Planet &planet, StateRenderCache *cache) {
    bind();
    Model *orb;
    switch (planet.lod) {
        case GameState::BILLBOARD:
            orb = cache->orb_2.get();
            break;
        case GameState::DISTANT:
            orb = cache->orb_3.get();
            break;
        case GameState::NEAR:
            orb = cache->orb_4.get();
            break;
        case GameState::ATMOSPHERE:
            orb = cache->orb_5.get();
            break;
    }
    loadMesh(orb->getMeshes()[0]);
    bindTexture(CUBEMAP_TEX_UNIT, *cache->planetResources[planet.id]->planetSurfaceMap->texture);
    cache->planetResources[planet.id]->matBlock->setBindingPoint(UniformBlock::MATERIAL);
    cache->planetResources[planet.id]->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    orb->getMeshes()[0]->draw();
}
