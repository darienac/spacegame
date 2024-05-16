//
// Created by dacma on 5/14/2024.
//

#include "StateRenderCache.h"
#include "glm/ext/matrix_transform.hpp"

glm::mat4 StateRenderCache::getModelTransformMatrix(glm::vec3 pos, float scale) {
    return glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), {scale, scale, scale});
}

void StateRenderCache::syncPlanetsToState(GameState *state) {
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
                .modelTransform = getModelTransformMatrix(state->planet.position, state->planet.radius),
                .surfaceMat = new Material({1.0f, 1.0f, 1.0f}, state->planet.surfaceColor, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 1.0f),
                .liquidMat = new Material({1.0f, 1.0f, 1.0f}, state->planet.liquidColor, {0.2f, 0.2f, 0.2f}, {0.0f, 0.0f, 0.0f}, 1.0f),
                .matBlock = nullptr,
                .planetSurfaceMap = new Cubemap(256, false, GL_RED, GL_RED)
        };
        PlanetData *data = planetResources[state->planet.id];
        data->matBlock = new UniformBlock({data->surfaceMat, data->liquidMat});
        perlinRenderer->drawToCubemap(&state->planet.surfaceNoise, data->planetSurfaceMap);
    }
}

void StateRenderCache::syncStarsToState(GameState *state) {
    for (auto it = starResources.cbegin(); it != starResources.cend();) {
        if (it->first != state->star.id) {
            delete it->second->material;
            delete it->second->matBlock;
            it = starResources.erase(it);
        } else {
            it++;
        }
    }
    if (!starResources.count(state->star.id)) {
        starResources[state->star.id] = new StarData {
            .modelTransform = getModelTransformMatrix(state->star.position, state->star.radius),
            .material = new Material({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, state->star.color, 1.0f),
            .matBlock = nullptr
        };
        StarData *data = starResources[state->star.id];
        data->matBlock = new UniformBlock(data->material);
    }
}

StateRenderCache::StateRenderCache(IPerlinRenderer *perlinRenderer): perlinRenderer(perlinRenderer) {
    blueOrb = new Model("blue_orb.obj");
    skybox = new Model("inverse_cube.obj");
    cameraCubemap = new Cubemap(256, true, GL_RGB, GL_RGB);
}

void StateRenderCache::syncToState(GameState *state) {
    syncPlanetsToState(state);
    syncStarsToState(state);
}

StateRenderCache::~StateRenderCache() {
    delete blueOrb;
    delete skybox;
    delete cameraCubemap;
}
