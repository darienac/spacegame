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

GameRenderer::GameRenderer(GameState *state, ResourceCache* cache): state(state), shader3D(cache->sceneShader), shader2D(cache->shader2D), cache(cache), camera(cache->window) {

}

void GameRenderer::drawScene() {
    if (cache->window->getWidth() == 0 || cache->window->getHeight() == 0) {
        return;
    }
    updateCamera();

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    cache->planetShader->bind();
//    cache->planetShader->loadEnvironment(&cache->basicEnv);
//    cache->planetShader->loadCamera(&camera, glm::mat4(1.0f));
//    cache->planetShader->drawModel(cache->blueOrb);

    cache->perlinShader->bind();
    cache->perlinShader->draw();
}
