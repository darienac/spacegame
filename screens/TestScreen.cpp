//
// Created by dacma on 2/21/2024.
//

#include <iostream>
#include "TestScreen.h"

TestScreen::TestScreen(ResourceCache *cache): renderer(&state, cache), engine(&state, cache->controls) {
    this->cache = cache;
}

void TestScreen::enable() {

}

void TestScreen::disable() {

}

void TestScreen::renderFrame() {
    renderer.drawScene();
}

void TestScreen::tick() {
    engine.tick();
}

bool TestScreen::shouldClose() {
    return close;
}

void TestScreen::requestClose() {
    close = true;
}

TestScreen::~TestScreen() {
}


