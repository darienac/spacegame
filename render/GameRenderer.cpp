//
// Created by dacma on 3/29/2024.
//

#include "GameRenderer.h"
#include "../GlobalFlags.h"

void GameRenderer::updateCamera() {
    camera.setPos(state->camera.pos);
    camera.setTarget(state->camera.pos + state->camera.dir);
    camera.setUp(state->camera.up);
}

void GameRenderer::drawPlanet(GameState::Planet &planet) {
    if (planet.lod >= GameState::GROUND) {
        return;
    }
    StateRenderCache::PlanetData *planetData = cache->stateRenderCache->planetResources[planet.id].get();
    cache->planetShader->bind();
    cache->planetShader->loadCamera(&camera, planetData->modelTransform);
    cache->planetShader->drawPlanet(planet, cache->stateRenderCache.get());
}

void GameRenderer::drawPlanetAtmosphere(GameState::Planet &planet) {
    StateRenderCache::PlanetData *data = cache->stateRenderCache->planetResources[planet.id].get();
    cache->atmosphereShader->bind();
    cache->atmosphereShader->loadCamera(&camera, data->atmosphereModelTransform);
    cache->atmosphereShader->loadMesh(data->mesh);
    data->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    data->mesh->draw();
}

void GameRenderer::drawPlanetHeightmap(GameState::Planet &planet) {
    StateRenderCache::PlanetData *data = cache->stateRenderCache->planetResources[planet.id].get();
    cache->heightmapShader->bind();
    cache->heightmapShader->loadCamera(&camera, data->heightmapModelTransform * *data->planetHeightmap->getRotation());
    cache->heightmapShader->loadMesh(data->planetHeightmap->getMesh());
    cache->heightmapShader->bindDiffuseTexture(*data->planetHeightmap->getNoiseTexture());
    data->matBlock->setBindingPoint(UniformBlock::MATERIAL);
    data->planetDataBlock->setBindingPoint(UniformBlock::PLANET_PROPS);
    glDepthFunc(GL_LEQUAL);
    data->planetHeightmap->getMesh()->draw();
    glDepthFunc(GL_LESS);
}

void GameRenderer::drawStar(GameState::Star &star) {
    StateRenderCache::StarData *starData = cache->stateRenderCache->starResources[star.id].get();
    cache->sceneShader->bind();
    cache->sceneShader->loadCamera(&camera, starData->modelTransform);
    cache->sceneShader->loadMesh(cache->stateRenderCache->orb_2->getMeshes()[0]);
    Shader3D::loadMaterialBlock(cache->stateRenderCache->starResources[star.id]->matBlock.get());
    cache->stateRenderCache->orb_2->getMeshes()[0]->draw();
}

void GameRenderer::doRenderTasks() {
    std::size_t numTransparent = 0;
    std::size_t numOpaque = 0;
    for (auto &task : renderTasks) {
        if (task.usesTransparency) {
            numTransparent++;
        } else {
            numOpaque++;
        }
    }
    std::vector<RenderTask*> sortedTransparent;
    std::vector<RenderTask*> sortedOpaque;
    sortedTransparent.reserve(numTransparent);
    sortedOpaque.reserve(numOpaque);
    for (auto &task : renderTasks) {
        if (task.usesTransparency) {
            sortedTransparent.push_back(&task);
        } else {
            sortedOpaque.push_back(&task);
        }
    }

    std::sort(sortedTransparent.begin(), sortedTransparent.end(), [this](RenderTask* a, RenderTask* b) {
        return glm::distance(camera.getPos(), a->pos) > glm::distance(camera.getPos(), b->pos);
    });
    std::sort(sortedOpaque.begin(), sortedOpaque.end(), [this](RenderTask* a, RenderTask* b) {
        return glm::distance(camera.getPos(), a->pos) < glm::distance(camera.getPos(), b->pos);
    });
    for (auto &task : sortedOpaque) {
        runRenderTask(*task);
    }
    for (auto &task : sortedTransparent) {
        runRenderTask(*task);
    }

    renderTasks.clear();
}

void GameRenderer::runRenderTask(GameRenderer::RenderTask &task) {
    switch (task.type) {
        case STAR:
            drawStar(*task.star);
            break;
        case PLANET:
            drawPlanet(*task.planet);
            break;
        case PLANET_ATMOSPHERE:
            drawPlanetAtmosphere(*task.planet);
            break;
        case PLANET_HEIGHTMAP:
            drawPlanetHeightmap(*task.planet);
            break;
    }
}

GameRenderer::GameRenderer(GameState *state, ResourceCache* cache): state(state), cache(cache), camera(cache->window) {
    cache->spaceShader->bind();
    cache->spaceShader->loadPerlinConfig(state->spaceNoise, glm::mat4(1.0f));
    cache->spaceShader->draw(cache->stateRenderCache->cameraCubemap.get());
}

void GameRenderer::drawScene() {
    if (cache->window->getWidth() == 0 || cache->window->getHeight() == 0) {
        return;
    }
    updateCamera();
    cache->stateRenderCache->syncToState(state);

    cache->screenBuffer->bind();

    cache->skyboxShader->bind();
    cache->skyboxShader->bindTexture(Shader3D::CUBEMAP_TEX_UNIT, *cache->stateRenderCache->cameraCubemap->texture);
    cache->skyboxShader->loadCamera(&camera, glm::translate(glm::mat4(1.0f), camera.getPos()));
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    cache->skyboxShader->drawModel(cache->stateRenderCache->skybox.get());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    for (auto &pair : state->planets) {
        renderTasks.emplace_back(RenderTask{
            .type = PLANET,
            .usesTransparency = false,
            .pos = pair.second->position,
            .planet = pair.second
        });
        renderTasks.emplace_back(RenderTask{
            .type = PLANET_ATMOSPHERE,
            .usesTransparency = true,
            .pos = pair.second->position,
            .planet = pair.second
        });
        if (pair.second->lod >= GameState::ATMOSPHERE) {
            renderTasks.emplace_back(RenderTask{
                    .type = PLANET_HEIGHTMAP,
                    .usesTransparency = false,
                    .pos = {0.0f, 0.0f, 0.0f},
                    .planet = pair.second
            });
        }
    }
    for (auto &pair : state->stars) {
        renderTasks.emplace_back(RenderTask{
            .type = STAR,
            .usesTransparency = false,
            .pos = pair.second->position,
            .star = pair.second
        });
    }

    doRenderTasks();
}

void GameRenderer::debugViewTexture(const Texture &texture) {
    cache->screenBuffer->bind();
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glDisable(GL_CULL_FACE);
    updateCamera();
    cache->stateRenderCache->syncToState(state);
    cache->shader2D->draw(texture);
}
