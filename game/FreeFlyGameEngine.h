//
// Created by dacma on 5/1/2024.
//

#ifndef SPACEGAME_FREEFLYGAMEENGINE_H
#define SPACEGAME_FREEFLYGAMEENGINE_H


#include "IGameEngine.h"
#include "state/GameState.h"
#include "../Controls.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class FreeFlyGameEngine: public IGameEngine {
private:
    static const inline float SCALE_MULT = 1.001;
    static const inline glm::vec3 SCALE_POS = {-10000.0f, 0.0f, 0.0f};
    static const inline float SCALE_BORDER_RADIUS = 1.0f;
    static const inline bool ORIENT_TO_PLANET = false;

    float camSpeed;
    float camRotSpeed;

    GameState *state;
    Controls *controls;

    static void updatePlanetLOD(GameState &state, GameState::Planet &planet);
    static void updateStarLOD(GameState &state, GameState::Star &star);
public:
    FreeFlyGameEngine(GameState* state, Controls* controls);

    void tick() override;
};


#endif //SPACEGAME_FREEFLYGAMEENGINE_H
