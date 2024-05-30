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
            it = planetResources.erase(it);
        } else {
            it++;
        }
    }
    for (auto &pair : state->planets) {
        GameState::Planet *planet = pair.second;
        boost::uuids::uuid id = pair.first;
        if (planetResources.contains(id)) {
            PlanetData *data = planetResources[id].get();
            if (data->planetHeightmap && glm::dot(glm::normalize(state->camera.pos - planet->position), *data->planetHeightmap->getLastPos()) < HMAP_UPDATE_THRESHOLD) {
                data->planetHeightmap->updateToPosition(state->camera.pos - planet->position);
            }
            continue;
        }
        int cubemapWidth;
        switch (planet->lod) {
            case GameState::BILLBOARD:
                cubemapWidth = 32;
                break;
            case GameState::DISTANT:
                cubemapWidth = 64;
                break;
            case GameState::NEAR:
                cubemapWidth = 256;
                break;
            case GameState::ATMOSPHERE:
                cubemapWidth = 1024;
                break;
        }
        planetResources[id] = std::make_unique<PlanetData>(PlanetData{
            .lod = planet->lod,
            .modelTransform = getModelTransformMatrix(planet->position, planet->radius),
            .atmosphereModelTransform = getModelTransformMatrix(planet->position, -(planet->radius + planet->atmosphereHeight)),
            .heightmapModelTransform = getModelTransformMatrix(planet->position, 1.0f),
            .surfaceMat = std::make_unique<Material>(glm::vec3{1.0f, 1.0f, 1.0f}, planet->surfaceColor, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f),
            .liquidMat = std::make_unique<Material>(glm::vec3{1.0f, 1.0f, 1.0f}, planet->liquidColor, glm::vec3{0.2f, 0.2f, 0.2f}, glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f),
            .matBlock = nullptr,
            .planetDataBlock = std::make_unique<UniformBlock>(*planet),
            .planetSurfaceMap = std::make_unique<Cubemap>(cubemapWidth, false, GL_RED, GL_RED),
            .mesh = getPlanetMesh(*planet),
        });
        PlanetData *data = planetResources[id].get();
        data->matBlock = std::make_unique<UniformBlock>(std::vector<Material*>{data->surfaceMat.get(), data->liquidMat.get()});
        perlinShader->drawToCubemap(&planet->surfaceNoise, data->planetSurfaceMap.get());
        if (planet->lod >= GameState::ATMOSPHERE) {
            data->planetHeightmap = std::make_unique<Heightmap>(*perlinShader, 20, 0.01, 5, 0.04, *planet);
            data->planetHeightmap->updateToPosition(state->camera.pos - planet->position);
        }
    }
}

void StateRenderCache::syncStarsToState(GameState *state) {
    for (auto it = starResources.cbegin(); it != starResources.cend();) {
        if (!state->stars.contains(it->first) || state->stars[it->first]->lod != starResources[it->first]->lod) {
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
        starResources[id] = std::make_unique<StarData>(StarData{
            .lod = star->lod,
            .modelTransform = getModelTransformMatrix(star->position, star->radius),
            .material = std::make_unique<Material>(glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 0.0f}, star->color, 1.0f),
            .matBlock = nullptr
        });
        StarData *data = starResources[id].get();
        data->matBlock = std::make_unique<UniformBlock>(data->material.get());
    }
}

Mesh *StateRenderCache::getPlanetMesh(GameState::Planet &planet) {
    Model *model;
    switch (planet.lod) {
        case GameState::BILLBOARD:
            model = orb_2.get();
            break;
        case GameState::DISTANT:
            model = orb_3.get();
            break;
        case GameState::NEAR:
            model = orb_4.get();
            break;
        case GameState::ATMOSPHERE:
            model = orb_5.get();
            break;
    }
    return model->getMeshes()[0];
}

StateRenderCache::StateRenderCache(ShaderPerlin *perlinShader): perlinShader(perlinShader) {
    orb_2 = std::make_unique<Model>("orb_2.obj");
    orb_3 = std::make_unique<Model>("orb_3.obj");
    orb_4 = std::make_unique<Model>("orb_4.obj");
    orb_5 = std::make_unique<Model>("orb_5.obj");
    skybox = std::make_unique<Model>("inverse_cube.obj");
    cameraCubemap = std::make_unique<Cubemap>(256, true, GL_RGB, GL_RGB);

    lightBlock = std::make_unique<UniformBlock>(UniformBlock::LIGHT);
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
