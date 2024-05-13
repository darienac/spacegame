//
// Created by dacma on 2/21/2024.
//

#ifndef CS455GAME_TESTSCREEN_H
#define CS455GAME_TESTSCREEN_H


#include "IScreen.h"
#include "../game/GameState.h"
#include "../render/GameRenderer.h"
#include "../game/FreeFlyGameEngine.h"
#include "ResourceCache.h"

class TestScreen : public IScreen {
private:
    bool close = false;
    ResourceCache *cache;
    GameState state;
    GameRenderer renderer;
    FreeFlyGameEngine engine;
public:
    TestScreen(ResourceCache* cache);

    void enable() override;
    void disable() override;
    void renderFrame() override;
    void tick() override;
    bool shouldClose() override;
    void requestClose() override;

    ~TestScreen() override;
};


#endif //CS455GAME_TESTSCREEN_H
