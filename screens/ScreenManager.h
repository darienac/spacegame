//
// Created by dacma on 2/20/2024.
//

#ifndef CS455GAME_SCREENMANAGER_H
#define CS455GAME_SCREENMANAGER_H


#include "../GlWindow.h"
#include "IScreen.h"
#include "TestScreen.h"
#include "ResourceCache.h"

class ScreenManager {
private:
    static const double TICK_RATE;

    ResourceCache *cache;
    int fps;
    int frameNum;
    int tickNum;

    IScreen* screen;
    TestScreen* testScreen;

    void updateCurrentScreen();
public:
    ScreenManager(ResourceCache* resourceCache);

    void run();
    void tick();

    ~ScreenManager();
};


#endif //CS455GAME_SCREENMANAGER_H
