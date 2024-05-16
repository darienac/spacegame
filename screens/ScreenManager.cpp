//
// Created by dacma on 2/20/2024.
//

#include "ScreenManager.h"
#include "TestScreen.h"
#include "../GlobalFlags.h"

const double ScreenManager::TICK_RATE = 600.0;

void ScreenManager::updateCurrentScreen() {
    switch (IScreen::currentScreen) {
        case IScreen::TEST:
            screen = testScreen;
            break;
        default:
            screen = nullptr;
            break;
    }
}

ScreenManager::ScreenManager(ResourceCache* resourceCache) {
    this->cache = resourceCache;

    testScreen = new TestScreen(resourceCache);
}

void ScreenManager::run() {
    double lastTime = glfwGetTime();
    double lastTickTime = lastTime;
    int fpsCounter = 0;
    tickNum = 0;
    fps = 0;
    frameNum = 0;
    GlWindow* window = cache->window;
    updateCurrentScreen();

    while (!screen->shouldClose()) {
        frameNum++;
        double time = glfwGetTime();
        fpsCounter++;
        if (time - lastTime >= 1.0) {
            lastTime++;
            fps = fpsCounter;
            fpsCounter = 0;
            if (GlobalFlags::SHOW_FPS) {
                std::cout << "FPS: " << fps << std::endl;
            }
        }

        if (glfwWindowShouldClose(window->getWindow())) {
            glfwSetWindowShouldClose(window->getWindow(), GLFW_FALSE);
            screen->requestClose();
        }

        if (time - lastTickTime >= (1.0 / TICK_RATE)) {
            int ticks = (time - lastTickTime) * TICK_RATE;
            lastTickTime += ticks / TICK_RATE;
            for (int i = 0; i < ticks; i++) {
                tick();
            }
        }

        if (cache->controls->fullscreenPressed) {
            cache->controls->fullscreenPressed = false;
            if (cache->window->isFullscreen()) {
                cache->window->disableFullscreen();
            } else {
                cache->window->enableFullscreen();
            }
        }
        if (window->isResized()) {
            glViewport(0, 0, window->getWidth(), window->getHeight());
            window->setResized(false);
        }
        screen->renderFrame();

//        glFinish();
        glfwSwapBuffers(window->getWindow());
        glfwPollEvents();
    }
}

void ScreenManager::tick() {
    cache->controls->pollGamepadInputs(0);
    screen->tick();
    tickNum++;
}

ScreenManager::~ScreenManager() {
    delete testScreen;
}
