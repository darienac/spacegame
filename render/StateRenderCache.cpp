//
// Created by dacma on 5/14/2024.
//

#include "StateRenderCache.h"

StateRenderCache::StateRenderCache(IPerlinRenderer *perlinRenderer): perlinRenderer(perlinRenderer) {
    blueOrb = new Model("blue_orb.obj");
    skybox = new Model("inverse_cube.obj");
}

void StateRenderCache::syncToState(GameState *state) {
    for (auto it = planetResources.cbegin(); it != planetResources.cend();) {
        if (it->first != state->planet.id) {
            delete it->second->surfaceMat;
            delete it->second->liquidMat;
            delete it->second->matBlock;
            it = planetResources.erase(it);
        } else {
            it++;
        }
    }
    if (!planetResources.count(state->planet.id)) {
        planetResources[state->planet.id] = new PlanetData {
                .surfaceMat = new Material({0.0f, 0.0f, 0.0f}, state->planet.surfaceColor, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 1.0f),
                .liquidMat = new Material({0.0f, 0.0f, 0.0f}, state->planet.liquidColor, {0.2f, 0.2f, 0.2f}, {0.0f, 0.0f, 0.0f}, 1.0f),
                .matBlock = nullptr,
                .planetSurfaceMap = new Cubemap(256, false, GL_RED, GL_RED)
        };
        PlanetData *data = planetResources[state->planet.id];
        data->matBlock = new UniformBlock({data->surfaceMat, data->liquidMat});
        perlinRenderer->drawToCubemap(&state->planet.surfaceNoise, data->planetSurfaceMap);
    }
}

StateRenderCache::~StateRenderCache() {
    delete blueOrb;
    delete skybox;
}
