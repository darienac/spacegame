//
// Created by dacma on 2/20/2024.
//

#ifndef CS455GAME_ISCREEN_H
#define CS455GAME_ISCREEN_H


#include "../GlWindow.h"

class IScreen {
public:
    enum ScreenName {
        TEST
    };
    inline static ScreenName currentScreen = TEST;

    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual void renderFrame() = 0;
    virtual void tick() = 0;
    virtual bool shouldClose() = 0;
    virtual void requestClose() = 0;

    virtual ~IScreen() = default;
};


#endif //CS455GAME_ISCREEN_H
