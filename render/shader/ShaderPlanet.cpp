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
    loadMesh(cache->blueOrb->getMeshes()[0]);
    bindTexture(GL_TEXTURE1, *cache->planetResources[planet.id]->planetSurfaceMap->texture);
    cache->planetResources[planet.id]->matBlock->setBindingPoint(UniformBlock::MATERIAL);
    cache->blueOrb->getMeshes()[0]->draw();
}
