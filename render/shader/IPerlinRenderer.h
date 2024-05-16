//
// Created by dacma on 5/15/2024.
//

#ifndef SPACEGAME_IPERLINRENDERER_H
#define SPACEGAME_IPERLINRENDERER_H

#include "../../game/GameState.h"
#include "../model/Cubemap.h"

class IPerlinRenderer {
public:
    virtual void drawToCubemap(GameState::PerlinNoise *noise, Cubemap *cubemap) = 0;
};

#endif //SPACEGAME_IPERLINRENDERER_H
