//
// Created by dacma on 6/7/2024.
//

#ifndef SPACEGAME_MAINGAMEENGINE_H
#define SPACEGAME_MAINGAMEENGINE_H


#include "BasicGameEngine.h"
#include "../Controls.h"

class MainGameEngine: public BasicGameEngine {
private:
    GameState *state;
    Controls *controls;
public:
    MainGameEngine(GameState* state, Controls* controls);

    void tick() override;
};


#endif //SPACEGAME_MAINGAMEENGINE_H
