//
// Created by dacma on 5/1/2024.
//

#ifndef SPACEGAME_FREEFLYGAMEENGINE_H
#define SPACEGAME_FREEFLYGAMEENGINE_H


#include "state/GameState.h"
#include "../Controls.h"
#include "BasicGameEngine.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class FreeFlyGameEngine: public BasicGameEngine {
private:
    static const inline double SCALE_MULT = 1.001;
    static const inline glm::dvec3 SCALE_POS = {-10000.0, 0.0, 0.0};
    static const inline double SCALE_BORDER_RADIUS = 1000.0;
    static const inline bool ORIENT_TO_PLANET = false;

    double camSpeed;
    double camRotSpeed;

    GameState *state;
    Controls *controls;
public:
    FreeFlyGameEngine(GameState* state, Controls* controls);

    void tick() override;
};


#endif //SPACEGAME_FREEFLYGAMEENGINE_H
