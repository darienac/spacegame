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
    StateRenderCache::PlanetData *planetData = cache->stateRenderCache->planetResources[planet.id];
    cache->planetShader->bind();
    cache->planetShader->loadCamera(&camera, planetData->modelTransform);
    cache->planetShader->drawPlanet(planet, cache->stateRenderCache.get());
}

void GameRenderer::drawStar(GameState::Star &star) {
    StateRenderCache::StarData *starData = cache->stateRenderCache->starResources[star.id];
    cache->sceneShader->bind();
    cache->sceneShader->loadCamera(&camera, starData->modelTransform);
    cache->sceneShader->loadMesh(cache->stateRenderCache->blueOrb->getMeshes()[0]);
    Shader3D::loadMaterialBlock(cache->stateRenderCache->starResources[star.id]->matBlock);
    cache->stateRenderCache->blueOrb->getMeshes()[0]->draw();
}

GameRenderer::GameRenderer(GameState *state, ResourceCache* cache): state(state), shader3D(cache->sceneShader.get()), shader2D(cache->shader2D.get()), cache(cache), camera(cache->window) {
    cache->spaceShader->bind();
    cache->spaceShader->loadPerlinConfig(state->spaceNoise);
    cache->spaceShader->draw(cache->stateRenderCache->cameraCubemap);
}

void GameRenderer::drawScene() {
    if (cache->window->getWidth() == 0 || cache->window->getHeight() == 0) {
        return;
    }
    cache->stateRenderCache->syncToState(state);
    updateCamera();

    cache->screenBuffer->bind();
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cache->skyboxShader->bind();
    cache->skyboxShader->bindTexture(Shader3D::CUBEMAP_TEX_UNIT, *cache->stateRenderCache->cameraCubemap->texture);
    cache->skyboxShader->loadCamera(&camera, glm::translate(glm::mat4(1.0f), camera.getPos()));
    glDisable(GL_DEPTH_TEST);
    cache->skyboxShader->drawModel(cache->stateRenderCache->skybox);
    glEnable(GL_DEPTH_TEST);

    for (auto &pair : state->planets) {
        drawPlanet(*pair.second);
    }
    for (auto &pair : state->stars) {
        drawStar(*pair.second);
    }
}
