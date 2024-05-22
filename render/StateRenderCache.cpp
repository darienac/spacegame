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
        if (!state->planets.contains(it->first) || state->planets[it->first]->lod != planetResources[it->first]->lod) {
            delete it->second->surfaceMat;
            delete it->second->liquidMat;
            delete it->second->matBlock;
            delete it->second->planetDataBlock;
            delete it->second->planetSurfaceMap;
            it = planetResources.erase(it);
        } else {
            it++;
        }
    }
    for (auto &pair : state->planets) {
        GameState::Planet *planet = pair.second;
        boost::uuids::uuid id = pair.first;
        if (planetResources.contains(id)) {
            continue;
        }
        auto *data = new PlanetData {
                .modelTransform = getModelTransformMatrix(planet->position, planet->radius),
                .surfaceMat = new Material({1.0f, 1.0f, 1.0f}, planet->surfaceColor, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, 1.0f),
                .liquidMat = new Material({1.0f, 1.0f, 1.0f}, planet->liquidColor, {0.2f, 0.2f, 0.2f}, {0.0f, 0.0f, 0.0f}, 1.0f),
                .matBlock = nullptr,
                .planetDataBlock = new UniformBlock(*planet),
                .planetSurfaceMap = new Cubemap(256, false, GL_RED, GL_RED)
        };
        data->matBlock = new UniformBlock({data->surfaceMat, data->liquidMat});
        perlinRenderer->drawToCubemap(&planet->surfaceNoise, data->planetSurfaceMap);
        planetResources[id] = data;
    }
}

void StateRenderCache::syncStarsToState(GameState *state) {
    for (auto it = starResources.cbegin(); it != starResources.cend();) {
        if (!state->stars.contains(it->first) || state->stars[it->first]->lod != starResources[it->first]->lod) {
            delete it->second->material;
            delete it->second->matBlock;
            it = starResources.erase(it);
        } else {
            it++;
        }
    }
    for (auto &pair : state->stars) {
        GameState::Star *star = pair.second;
        boost::uuids::uuid id = pair.first;
        if (starResources.contains(id)) {
            continue;
        }
        auto *data = new StarData {
                .modelTransform = getModelTransformMatrix(star->position, star->radius),
                .material = new Material({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, star->color, 1.0f),
                .matBlock = nullptr
        };
        data->matBlock = new UniformBlock(data->material);
        starResources[id] = data;
    }
}

StateRenderCache::StateRenderCache(IPerlinRenderer *perlinRenderer): perlinRenderer(perlinRenderer) {
    blueOrb = new Model("blue_orb.obj");
    skybox = new Model("inverse_cube.obj");
    cameraCubemap = new Cubemap(256, true, GL_RGB, GL_RGB);

    lightBlock = new UniformBlock(UniformBlock::LIGHT);
    lightBlock->setBindingPoint(UniformBlock::LIGHT);
}

void StateRenderCache::syncToState(GameState *state) {
    syncPlanetsToState(state);
    syncStarsToState(state);
    std::vector<GameState::Light*> lights;
    for (auto &pair : state->lights) {
        lights.push_back(pair.second);
    }
    lightBlock->loadLights(lights, state->ambientLight);
}

StateRenderCache::~StateRenderCache() {
    delete blueOrb;
    delete skybox;
    delete cameraCubemap;
    delete lightBlock;
}
