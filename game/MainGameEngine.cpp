//
// Created by dacma on 6/7/2024.
//

#include "MainGameEngine.h"

MainGameEngine::MainGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {

}

void MainGameEngine::tick() {
    updateLODs(*state);
}
