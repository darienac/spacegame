//
// Created by dacma on 5/14/2024.
//

#include "ShaderPlanet.h"
#include "UniformBlock.h"

ShaderPlanet::ShaderPlanet(const std::vector<std::string> &vertexShader, const std::vector<std::string> &fragmentShader): Shader3D(vertexShader, fragmentShader) {}

void ShaderPlanet::drawPlanet(GameState::Planet &planet, StateRenderCache *cache) {
    StateRenderCache::PlanetData *data = cache->planetResources[planet.id].get();
    bind();
    loadMesh(data->mesh);
    bindTexture(CUBEMAP_TEX_UNIT, *data->planetSurfaceMap->texture);
    data->matBlock->setBindingPoint(UniformBlock::MATERIAL);
    data->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    data->mesh->draw();
}
