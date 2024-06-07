//
// Created by dacma on 5/1/2024.
//

#include <iostream>
#include "FreeFlyGameEngine.h"
#include "../GlobalFlags.h"

void FreeFlyGameEngine::tick() {
    // logic for a free flying camera, no game logic happening otherwise
    glm::vec3 camZ = -state->camera.dir;
    glm::vec3 camX = glm::normalize(glm::cross(state->camera.up, camZ));
    glm::vec3 camY = glm::cross(camZ, camX);
    state->camera.pos += camSpeed * controls->debugFlyXZDir.x * camX;
    state->camera.pos -= camSpeed * controls->debugFlyXZDir.y * camZ;
    if (controls->debugRiseButtonDown) {
        state->camera.pos += camSpeed * state->camera.up;
    }
    if (controls->debugFallButtonDown) {
        state->camera.pos -= camSpeed * state->camera.up;
    }
    if (controls->debugApproachButtonDown) {
        float adjustedCenterDist = (glm::length(state->camera.pos - SCALE_POS) - SCALE_BORDER_RADIUS) / SCALE_MULT + SCALE_BORDER_RADIUS;
        state->camera.pos = glm::normalize(state->camera.pos - SCALE_POS) * adjustedCenterDist + SCALE_POS;
        camSpeed /= SCALE_MULT;
    }
    if (controls->debugDivergeButtonDown) {
        float adjustedCenterDist = (glm::length(state->camera.pos - SCALE_POS) - SCALE_BORDER_RADIUS) * SCALE_MULT + SCALE_BORDER_RADIUS;
        state->camera.pos = glm::normalize(state->camera.pos - SCALE_POS) * adjustedCenterDist + SCALE_POS;
        camSpeed *= SCALE_MULT;
    }
    state->camera.dir = glm::rotate(glm::mat4(1.0f), -camRotSpeed * controls->debugPanCameraDir.x, camY) * glm::vec4(state->camera.dir, 0.0f);
    state->camera.dir = glm::rotate(glm::mat4(1.0f), camRotSpeed * controls->debugPanCameraDir.y, camX) * glm::vec4(state->camera.dir, 0.0f);
    if (ORIENT_TO_PLANET) {
        state->camera.up = glm::normalize(state->camera.pos - SCALE_POS);
    }

    updateLODs(*state);
}

FreeFlyGameEngine::FreeFlyGameEngine(GameState *state, Controls *controls): state(state), controls(controls) {
    camSpeed = 10.0f;
    camRotSpeed = 0.002f;
}