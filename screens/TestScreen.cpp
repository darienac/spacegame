//
// Created by dacma on 2/21/2024.
//

#include <iostream>
#include "TestScreen.h"
#include "../GlobalFlags.h"

TestScreen::TestScreen(ResourceCache *cache): renderer(&state, cache), debugEngine(&state, cache->controls.get()), mainEngine(&state, cache->controls.get()) {
    this->cache = cache;
}

void TestScreen::enable() {

}

void TestScreen::disable() {

}

void TestScreen::renderFrame() {
    renderer.drawScene();
//    GameState::Planet *planet = &state.planet;
//    cache->stateRenderCache->syncToState(&state);
//    renderer.debugViewTexture(*cache->stateRenderCache->planetResources[planet->id]->planetHeightmap->getNoiseTexture());
}

void TestScreen::tick() {
    if (GlobalFlags::DEBUG && cache->controls->enableDebugEngine) {
        debugEngine.tick();
    } else {
        mainEngine.tick();
    }
}

bool TestScreen::shouldClose() {
    return close;
}

void TestScreen::requestClose() {
    close = true;
}

TestScreen::~TestScreen() {
}


