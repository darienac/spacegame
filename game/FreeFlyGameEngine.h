//
// Created by dacma on 5/1/2024.
//

#ifndef SPACEGAME_FREEFLYGAMEENGINE_H
#define SPACEGAME_FREEFLYGAMEENGINE_H


#include "IGameEngine.h"
#include "GameState.h"
#include "../Controls.h"

class FreeFlyGameEngine: public IGameEngine {
private:
    static float camSpeed;
    static float camRotSpeed;

    GameState *state;
    Controls *controls;
public:
    FreeFlyGameEngine(GameState* state, Controls* controls);

    void tick() override;
};


#endif //SPACEGAME_FREEFLYGAMEENGINE_H
