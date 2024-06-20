//
// Created by dacma on 6/7/2024.
//

#ifndef SPACEGAME_BASICGAMEENGINE_H
#define SPACEGAME_BASICGAMEENGINE_H


#include "IGameEngine.h"
#include "../state/GameState.h"

class BasicGameEngine: public IGameEngine {
protected:
    static void updatePlanetLOD(GameState &state, GameState::Planet &planet);
    static void updateStarLOD(GameState &state, GameState::Star &star);
    static void updateLODs(GameState &state);
};


#endif //SPACEGAME_BASICGAMEENGINE_H
